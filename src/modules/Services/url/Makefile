#
# Cosmos Project
# Makefile for generic service module
# version: 2020-03-26rh


#### INPUT ####

SRCNAME = cosmos_service_module.c


#### OUTPUT ####

LIBNAME = service.so
BINNAME = service
INCLDIR = /usr/local/include

#### DEPENDENCIES ####

CC = gcc
CURLLIBNAME = curl


#### DIRS ####

SRC = src
BINOUT = bin
LIBOUT = lib


#### BUILD TOOL ARGS ####

CCARGS = -g
CCARGS-SHARED = -fPIC -shared



#### BUILD TARGETS ####

all: service

service: dirs
	$(CC) $(CCARGS) $(SRC)/$(SRCNAME) -o $(BINOUT)/$(BINNAME) -I$(INCLDIR) -l$(CURLLIBNAME)
	$(CC) $(CCARGS) $(CCARGS-SHARED) $(SRC)/$(SRCNAME) -o $(LIBOUT)/$(LIBNAME) -I$(INCLDIR) -l$(CURLLIBNAME)


dirs:
	mkdir -p $(LIBOUT)
	mkdir -p $(BINOUT)

