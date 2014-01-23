#!/usr/bin/make

HOME=/home1/00479/willmore

INCLUDE_DIR=$(HOME)/usr/include
INSTALL_DIR=$(HOME)/usr/bin
LIBRARY_DIR=$(HOME)/usr/lib

CC=icc

cv:	cv.c
	$(CC) cv.c -Wall -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) -lm -lftw -o cv 
	mv cv $(INSTALL_DIR)

csa:	csa.c
	$(CC) csa.c -Wall -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) -lm -lftw -o csa 
	mv csa $(INSTALL_DIR)

spackle:	spackle.c
	$(CC) spackle.c -Wall -I$(INCLUDE_DIR)  -L$(LIBRARY_DIR) -lm -lftw -o spackle
	mv spackle $(INSTALL_DIR)

cell_volume:	cell_volume.c
	$(CC) cell_volume.c -Wall -I$(INCLUDE_DIR)  -L$(LIBRARY_DIR) -lm -lftw -o cell_volume 
	mv cell_volume $(INSTALL_DIR)

boxv:	boxv.c
	$(CC) boxv.c -Wall -I$(INCLUDE_DIR)  -L$(LIBRARY_DIR) -lm -lftw -o boxv 
	mv boxv $(INSTALL_DIR)

asph:	asph.c
	$(CC) asph.c -Wall -I$(INCLUDE_DIR)  -L$(LIBRARY_DIR) -lm -lftw -o asph
	mv asph $(INSTALL_DIR)

sample:	sample.c
	$(CC) sample.c -Wall -I$(INCLUDE_DIR)  -L$(LIBRARY_DIR) -lm -lftw -o sample

install:	csa cv asph

