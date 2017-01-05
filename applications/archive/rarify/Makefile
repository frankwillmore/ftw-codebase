#!/usr/bin/make

INSTALL_DIR=/home/willmore

rarify:	rarify.c
	gcc rarify.c -I$(INSTALL_DIR)/usr/include -L$(INSTALL_DIR)/lib -lftw -o rarify

install:	rarify
	mv rarify $(INSTALL_DIR)/bin
