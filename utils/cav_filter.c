/* cav_filter.c */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ftw_config_parser.h>
#include <ftw_param.h>
#include <ftw_types.h>

// IN:	input stream of gfg from stdin
// OUT: output stream of replicas
main(int argc, char* argv[])
{
  int i, j, k;
  int mirror_depth;
  char line[256];
  double x, y, z;
  double min=0.0;
  double max=1e+308;

  setCommandLineParameters(argc, argv);
  if (getFlagParam("-usage")) {
    printf("cav_filter -min x.xxx -max x.xxx\t include only cavities with specified diameter range.\n\n");
    exit(0);
  }
  getDoubleParam("-min", &min);
  getDoubleParam("-max", &max);

  while (1) {
    fgets(line, 256, stdin);
    if (feof(stdin)) break;
    
    char *xs = strtok(line, "\t");
    char *ys = strtok(NULL, "\t");
    char *zs = strtok(NULL, "\t");
    char *ds = strtok(NULL, "\n");

    double x = strtod(xs, NULL);
    double y = strtod(ys, NULL);
    double z = strtod(zs, NULL);
    double d = strtod(ds, NULL);

    if (d > min && d < max) printf("%lf\t%lf\t%lf\t%lf\n", x, y, z, d);
  }
 
  fclose(stdin);

}


