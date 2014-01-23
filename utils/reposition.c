/* reposition.c */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ftw_config_parser.h>
#include <ftw_param.h>
#include <ftw_types.h>

main(int argc, char* argv[]) {
  char line[256];
  double x, y, z;
  double shift_x, shift_y, shift_z;

  setCommandLineParameters(argc, argv);
  if (getFlagParam("-usage")) {
    printf("reposition [-shift x.xxx y.yyy z.zzz]\n\n");
    printf("moves all coordinates by specified amount.\n");
    printf("IN:  \t.gfg or .cav\n");
    printf("OUT: \t.gfg or .cav\n");
    exit(0);
  }
  if (!getFlagParam("-shift")) {
    printf("No shift specified.\n");
    return(1);
  }
  else getVectorParam("-shift", &shift_x, &shift_y, &shift_z);

  while (1) {
    fgets(line, 256, stdin);
    if (feof(stdin)) break;
    
    char *xs = strtok(line, "\t");
    char *ys = strtok(NULL, "\t");
    char *zs = strtok(NULL, "\t");
    char *ss = strtok(NULL, "\n");

    double x = strtod(xs, NULL);
    double y = strtod(ys, NULL);
    double z = strtod(zs, NULL);

    printf("%lf\t%lf\t%lf\t%s\n", x + shift_x, y + shift_y, z + shift_z, ss);
  }
 
  fclose(stdin);
}


