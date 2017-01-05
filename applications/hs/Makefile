#!/usr/bin/make

INSTALL_DIR=/home/willmore

INCLUDES=-I$(INSTALL_DIR)/usr/include/
CFLAGS=-O3 -Wall
CC=gcc
LIBS=-lm -lX11 -lftw 
LIB_DIRS= -L$(INSTALL_DIR)/lib/ -L/usr/X11R6/lib/

hs:	io_setup.o graphics.o hs_main.c hs_main.h
	gcc *.o hs_main.c -o hs -I$(INSTALL_DIR)/usr/include/ -L$(INSTALL_DIR)/lib/ -L/usr/X11R6/lib -lm -lX11 -lftw -O3 -Wall

io_setup.o:	io_setup.c
	gcc -c io_setup.c -I$(INSTALL_DIR)/usr/include -L$(INSTALL_DIR)/lib -lftw -O3 -Wall

graphics.o:	graphics.c
	gcc -c graphics.c -I$(INSTALL_DIR)/usr/include -L/usr/X11R6/lib -O3 -Wall

install: hs
	cp hs $(INSTALL_DIR)/bin
	make clean

clean:
	rm *.o
