#!/usr/bin/make

HOME=/home1/00479/willmore/
CC=icc

INCLUDE_DIR=$(HOME)/usr/include
BINARY_DIR=$(HOME)/usr/bin
LIBRARY_DIR=$(HOME)/usr/lib

rog:	rog.c
	$(CC) rog.c -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) -lm -lftw -o rog

install:	rog
	mv rog $(BINARY_DIR)

