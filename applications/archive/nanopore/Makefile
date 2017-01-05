#!/usr/bin/make

INSTALL_DIR=/home/willmore

nanopore:	nanopore.c
	gcc nanopore.c -I$(INSTALL_DIR)/usr/include -L$(INSTALL_DIR)/lib -lftw -o nanopore

install:	nanopore
	mv nanopore $(INSTALL_DIR)/bin
