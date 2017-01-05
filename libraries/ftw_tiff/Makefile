#!/bin/make

#  Codes are packaged to install to user home by default

INSTALL_DIR:=$$HOME

TIFF_INCLUDE_DIR:=/usr/include

LIBRARY_DIR:=$(INSTALL_DIR)/usr/lib
INCLUDE_DIR:=$(INSTALL_DIR)/usr/include
BINARY_DIR:=$(INSTALL_DIR)/usr/bin

INCLUDES:=-I$(INCLUDE_DIR) -I$(TIFF_INCLUDE_DIR)
LIBS:=-L$(LIBRARY_DIR) 

CC:=gcc
CFLAGS=-O2 

echo:	
	@echo "Please specify a target, e.g. 'make install'"

ftw_makeTIFF.o:       ftw_makeTIFF.c ftw_makeTIFF.h
	$(CC) $(CFLAGS) $(INCLUDES) ftw_makeTIFF.h ftw_makeTIFF.c -c -I. -fPIC

libftw_tiff.so:	ftw_makeTIFF.o
	$(CC) $(CFLAGS) -shared -o libftw_tiff.so ftw_makeTIFF.o -fPIC 

example:  example.c libftw_tiff.so
	$(CC) -L$(LIBRARY_DIR) $(INCLUDES) example.c -ltiff -lftw_tiff -o example

clean:
	rm -f ftw_makeTIFF.o libftw_tiff.so

install:  install-lib install-header

install-header:	ftw_makeTIFF.h
	cp ftw_makeTIFF.h $(INCLUDE_DIR)

install-lib:  libftw_tiff.so
	mv libftw_tiff.so $(LIBRARY_DIR)

.PHONY:  install install-header install-lib clean

