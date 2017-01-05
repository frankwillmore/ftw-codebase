###############################################################################

There are Makefiles in each directory where code can be built. The essential 
codes that must be built are:

<< essential headers, libs >>

Applications and utilities depend on these, so build these first. 

Codes here obey standard Linux FHS for install, i.e. they will install to 
$INSTALL_PREFIX/usr/{lib, include, bin}. To build a code, go to the directory 
with the Makefile and type:

make CC=cc INSTALL_PREFIX=/path/to/where/you/want/to/install install 

e.g., I want to compile with cc and install to my $WORK directory:

cd libraries/general && make CC=cc INSTALL_PREFIX=$WORK install && cd -
cd libraries/ftw_tiff && make CC=cc INSTALL_PREFIX=$WORK install && cd -
cd libraries/ftw_pov && make CC=cc INSTALL_PREFIX=$WORK install && cd -
cd utils && make CC=cc INSTALL_PREFIX=$WORK install && cd -

======

Plan: A master Makefile in the repo root dir, which will have targets to build
headers, essential targets, etc.

###############################################################################
