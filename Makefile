###############################################################################

# You might get luck and just type 'make' and be all good, provided 
# dependencies are installed.

INSTALL_DIR:=$(WORK)
CC:=cc

default:
	cd libraries/general && make CC=$(CC) INSTALL_DIR=$(INSTALL_DIR) install 
	cd libraries/ftw_tiff && make CC=$(CC) INSTALL_DIR=$(INSTALL_DIR) install 
	cd libraries/ftw_pov && make CC=$(CC) INSTALL_DIR=$(INSTALL_DIR) install 
	cd utils && make CC=$(CC) INSTALL_DIR=$(INSTALL_DIR) install 


###############################################################################
