/* ftw_config_parser.h */

#ifndef FTW_CONFIG_PARSER_H
#define FTW_CONFIG_PARSER_H

//  A set of library routines to parse input file

//  IN:  FILE* pointer to an input stream
//  OUT:  configuration, and metadata:  number of lines

#include <stdlib.h>
#include <stdio.h>
#include <ftw_param.h>
#include <string.h>

#include <ftw_types.h>

// return value is pointer to configuration

#ifdef __cplusplus
extern "C"
#endif
ftw_GFG65536 *readGFG65536(FILE *instream);

#ifdef __cplusplus
extern "C"
#endif
ftw_GFG65536 *replicateGFG65536(ftw_GFG65536 *in);

#ifdef __cplusplus
extern "C"
#endif
ftw_GFG16M *readGFG16M(FILE *instream);

#ifdef __cplusplus
extern "C"
#endif
ftw_GFG16M *replicateGFG16M(ftw_GFG16M *in);

#endif

