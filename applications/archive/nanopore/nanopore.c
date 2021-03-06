/* nanopore.c */

#define MAX_CAVITIES 1310720

#include <ftw_std.h>
#include "nanopore.h"

double box_x, box_y, box_z;

int isMarked[MAX_CAVITIES];
double x[MAX_CAVITIES], y[MAX_CAVITIES], z[MAX_CAVITIES], d[MAX_CAVITIES];
int number_of_cavities=0;
int pore_number=0;
int n_remaining;

int main(int argc, char* argv[])
{
  int i;

  setCommandLineParameters(argc, argv);
  getVectorParam("-box", &box_x, &box_y, &box_z);

  readInputStream();

  while (n_remaining > 0)
  {
    for(i=0; i<number_of_cavities; i++)
    {
//printf("initiating i=%d\n", i);
      if (!isMarked[i]) 
      {
        followChain(i);
        pore_number++;
      }
    }
  }
}

void followChain(int i)
{
  int j;

  isMarked[i]=1;
  printf("%d\t%lf\t%lf\t%lf\t%lf\n", pore_number, x[i], y[i], z[i], d[i]);
  n_remaining--;

  for (j=0; j<number_of_cavities; j++)
  if (!isMarked[j] && areOverlapping(i,j)) followChain(j);
}

int areOverlapping(int cav1, int cav2)
{
  double shift_x, shift_y, shift_z;
  double dx, dy, dz, d2, dx2, dy2, dz2;

  for (shift_x=0; shift_x <= box_x; shift_x += box_x)
  for (shift_y=0; shift_y <= box_y; shift_y += box_y)
  for (shift_z=0; shift_z <= box_z; shift_z += box_z)
  {
    dx=shift_x + x[cav1] - x[cav2]; 
    dy=shift_y + y[cav1] - y[cav2]; 
    dz=shift_z + z[cav1] - z[cav2]; 

    dx2=dx*dx;
    dy2=dy*dy;
    dz2=dz*dz;
   
    d2=(d[cav1]+d[cav2])*(d[cav1]+d[cav2])*.25;

    if (dx2+dy2+dz2 < d2) return 1;
  }

  return 0;
}

void readInputStream()
{
  char line[80];
  char *xs, *ys, *zs, *ds;

  while (TRUE)
  {
    fgets(line, 80, stdin);
    if (feof(stdin)) break;

    xs = strtok(line, "\t");
    ys = strtok(NULL, "\t");
    zs = strtok(NULL, "\t");
    ds = strtok(NULL, "\n");

    x[number_of_cavities] = strtod(xs, NULL);
    y[number_of_cavities] = strtod(ys, NULL);
    z[number_of_cavities] = strtod(zs, NULL);
    d[number_of_cavities] = strtod(ds, NULL);
    number_of_cavities++;

    if (number_of_cavities > MAX_CAVITIES)
    {
      printf("Too many cavities.");
      exit(0);
    }
  }

  n_remaining=number_of_cavities;
}
