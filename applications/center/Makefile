#!/usr/bin/make

HOME=/home1/00479/willmore

BINARY_DIR=$(HOME)/usr/bin
LIBRARY_DIR=$(HOME)/usr/lib
INCLUDE_DIR=$(HOME)/usr/include



center:	center.c
	gcc center.c -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) -lftw -o center
install:	center
	mv center $(BINARY_DIR)
