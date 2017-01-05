#!/usr/bin/make

HOME=/home1/00479/willmore

BINARY_DIR=$(HOME)/usr/bin
LIBRARY_DIR=$(HOME)/usr/lib
INCLUDE_DIR=$(HOME)/usr/include

cav2cluster:	cav2cluster.c
	gcc cav2cluster.c -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) -lftw -o cav2cluster -lm

install:	cav2cluster
	mv cav2cluster $(BINARY_DIR)
