/* gfg2fvi256.cu */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

extern "C" {
#include <ftw_param.h>
#include <ftw_config_parser.h>
#include <ftw_types.h>
}

ftw_EnergyArray256 *GFGToRepulsion256_612(ftw_GFG16M *gfg, float sigma, float epsilon);

//  IN:    A pointer to a ***non-replicated*** polymer configuration as *ftw_GFG16M.  
//  OUT:   A free volume intensity is returned as *ftw_FVI256.  
//  Input configuration is not modified.  
//  Cross-interaction values are stored for the replicated config only.

__global__ void EnergyKernel256_612(ftw_GFG16M *d_configuration, ftw_EnergyArray256 *d_attraction, ftw_EnergyArray256 *d_repulsion, ftw_EnergyArray256 *d_total) {
  unsigned int idx = blockIdx.x;
  unsigned int idy = blockIdx.y;
  unsigned int idz = threadIdx.x;

  float repulsion=0;
  float attraction=0;
  float sigma_over_r_sq;
  float dx, dy, dz, dd;
  float f_resolution_x = d_configuration->box_x / 256;
  float f_resolution_y = d_configuration->box_y / 256;
  float f_resolution_z = d_configuration->box_z / 256;

  float cuda_x = idx * f_resolution_x;
  float cuda_y = idy * f_resolution_y;
  float cuda_z = idz * f_resolution_z;

  // evaluate energy at (cuda_x, cuda_y, cuda_z);
  for (int i=0; i< d_configuration->n_atoms; i++) {
    // central atom
    dx = d_configuration->atom[i].x - cuda_x;
    dy = d_configuration->atom[i].y - cuda_y;
    dz = d_configuration->atom[i].z - cuda_z;
    dd = dx*dx + dy*dy + dz*dz; 
    sigma_over_r_sq = d_configuration->atom[i].sigma * d_configuration->atom[i].sigma / dd; // squared   
    repulsion += d_configuration->atom[i].epsilon * sigma_over_r_sq * sigma_over_r_sq * sigma_over_r_sq * sigma_over_r_sq * sigma_over_r_sq * sigma_over_r_sq;
    attraction += d_configuration->atom[i].epsilon * sigma_over_r_sq * sigma_over_r_sq * sigma_over_r_sq;
  } 

  // If NULL pointers are passed for the attraction or repulsion, no values are returned.
  if (d_attraction) d_attraction->energy[idx][idy][idz] = 4 * attraction;
  if (d_repulsion) d_repulsion->energy[idx][idy][idz] = 4 * repulsion;
  if (d_total) d_total->energy[idx][idy][idz] = 4 * repulsion - 4 * attraction;
}

ftw_EnergyArray256 *GFGToRepulsion256_612(ftw_GFG16M *gfg, float sigma, float epsilon)
{
  ftw_EnergyArray256 	*d_repulsion;
  ftw_GFG16M 		*d_configuration;

  // replicate the gfg
  ftw_GFG16M *h_configuration = replicateGFG16M(gfg); 

// and cross-parameterize use 6-12 rule
  for (int n=0; n<gfg->n_atoms; n++) {
    h_configuration->atom[n].sigma = 0.5f * (sigma + h_configuration->atom[n].sigma);
    h_configuration->atom[n].epsilon = sqrt(epsilon * h_configuration->atom[n].epsilon);
  }

  // then do the calc
  cudaError_t err;
  /* allocate for energy array and configuration on device */
  for(err = cudaErrorUnknown; err != cudaSuccess; err = cudaMalloc( (void **) &d_repulsion, sizeof(ftw_EnergyArray256)));
  for(err = cudaErrorUnknown; err != cudaSuccess; err = cudaMalloc( (void **) &d_configuration, sizeof(ftw_GFG16M)));
  for(err = cudaErrorUnknown; err != cudaSuccess; err = cudaMemcpy( d_configuration, h_configuration, sizeof(ftw_GFG16M), cudaMemcpyHostToDevice ));

  dim3 dimGrid(256, 256);
  dim3 dimBlock(256, 1, 1);

  EnergyKernel256_612<<< dimGrid, dimBlock >>>(d_configuration, NULL, d_repulsion, NULL);
  cudaThreadSynchronize(); // block until the device has completed
  err = cudaGetLastError();
  if (err != cudaSuccess) printf("%s\n", cudaGetErrorString(err)); 

  // retrieve result
  ftw_EnergyArray256 *h_repulsion = (ftw_EnergyArray256 *)malloc(sizeof(ftw_EnergyArray256));
  for(err = cudaErrorUnknown; err != cudaSuccess; err = cudaMemcpy(h_repulsion, d_repulsion, sizeof(ftw_EnergyArray256), cudaMemcpyDeviceToHost ));

  // free device memory
  cudaFree(d_configuration);
  cudaFree(d_repulsion);

  free(h_configuration); // free host memory for replicated configuration

  return h_repulsion;
}

main(int argc, char *argv[]) {
  int i,j,k;
  double box_x=10, box_y=10, box_z=10;
  int resolution = 256;
  int device_count;
  float attenuator = 1.68949;
  float preexponential = 1.0;
  float sigma=0.0;
  float epsilon=1.0;

  setCommandLineParameters(argc, argv);

  if (getFlagParam("-usage")) {
    printf("usage:     gfg2fvi        -box [10.0 10.0 10.0]\n");
    printf("                          -resolution [256] \n");
    printf("                          -attenuator [1.68949] \n");
    printf("                          -preexponential [1.0] \n");
    printf("                          -sigma [0.0] \n");
    printf("                          -epsilon [1.0] \n");
    printf("                          -check_device \n\n");
    printf("specifying preexponential of 10 will shift result left by one decimal place.\n");
    printf("fvi does not depend on temperature. To get a level surface at e.g. kT, \n");
    printf("Work units of attenuator as 1/kT for the given units of epsilon. E.g. \n");
    printf("if force field epsilon is in kcal/mol, then attenuator of 1.68949 is correct for T=298K.\n");
    printf("The level surface corresponds to E=kT, thus exp(E/-kT) = e^-1, 0.36787944117144.\n\n");
    exit(0);
  }

  if (getFlagParam("-check_device")) {
    printf("Checking for devices...\n");
    cudaGetDeviceCount(&device_count);
    printf("Found %d device(s).\n", device_count);
    exit(0);
  }

  getVectorParam("-box", &box_x, &box_y, &box_z);
  getIntParam("-resolution", &resolution);
  getFloatParam("-attenuator", &attenuator);
  getFloatParam("-preexponential", &preexponential);
  getFloatParam("-sigma", &sigma);
  getFloatParam("-epsilon", &epsilon);

  fprintf(stderr,"reading configuration\n");

  ftw_GFG16M *gfg = readGFG16M(stdin);
  gfg->box_x = box_x;
  gfg->box_y = box_y;
  gfg->box_z = box_z;

  fprintf(stderr, "calculating resolution = %d for 6-12 potential\n", resolution);
  fprintf(stderr, "using sigma = %f and epsilon = %f \n", sigma, epsilon);

  // ((resolution == 256) && (potential == 612))
  ftw_EnergyArray256 *ea = GFGToRepulsion256_612(gfg, sigma, epsilon);
  for (i=0; i<resolution; i++) for (j=0; j<resolution; j++) for (k=0; k<resolution; k++)
    printf("%f\t%f\t%f\t%f\n", i*box_x / resolution, j*box_y / resolution, k*box_z / resolution, 
			       preexponential * exp(ea->energy[i][j][k]/(-attenuator))); 
}

