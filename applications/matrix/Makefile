#!/usr/bin/make

INSTALL_DIR=/home1/00479/willmore

matrix:	matrix.c
	gcc matrix.c -I$(INSTALL_DIR)/usr/include -L$(INSTALL_DIR)/usr/lib -lftw -lm -o matrix
	mv matrix $(INSTALL_DIR)/usr/bin

xmatrix:	xmatrix.c
	gcc xmatrix.c -I$(INSTALL_DIR)/usr/include -L$(INSTALL_DIR)/usr/lib -lftw -lm -o xmatrix
	mv xmatrix $(INSTALL_DIR)/usr/bin

xmatrix2d:	xmatrix2d.c
	gcc xmatrix2d.c -I$(INSTALL_DIR)/usr/include -L$(INSTALL_DIR)/usr/lib -lftw -lm -o xmatrix2d
	mv xmatrix2d $(INSTALL_DIR)/usr/bin

matrix2d:	matrix2d.c
	gcc matrix2d.c -I$(INSTALL_DIR)/usr/include -L$(INSTALL_DIR)/usr/lib -lftw -lm -o matrix2d
	mv matrix2d $(INSTALL_DIR)/usr/bin
