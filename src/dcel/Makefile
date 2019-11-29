SHELL = /bin/bash

code-root = ../..

out-o = $(code-root)/out/o
out-bin = $(code-root)/out/bin
out-lib = $(code-root)/out/lib
out-modules = $(out-lib)/modules
out-test-bin = $(code-root)/out/test-bin

install-lib = ~/.cosm/lib/cosmos
install-lib-modules = $(install-lib)/modules

src-modules = ./modules

dbugopts = -g
warnopts = -Wall

devlib = $(code-root)/out/lib 


out-dirs:
	mkdir -p $(out-o)
	mkdir -p $(out-bin)
	mkdir -p $(out-lib)
	mkdir -p $(out-modules)
	mkdir -p $(out-test-bin)

install-dirs:
	mkdir -p $(install-lib)
	mkdir -p $(install-lib-modules)


all: out-dirs install-dirs tests utils


devdirs:  out-dirs


data-cell:
	gcc $(dbugopts) -fPIC -c data_cell.c -o $(out-o)/data_cell.o

data-cell-test:
	gcc $(dbugopts) $(out-o)/{dcel,frag,ptr_stack,btree_cpp,mfrag,data_cell}.o data_cell_test.c -o $(out-test-bin)/data-cell-test -lstdc++



dcel:   
	gcc $(dbugopts) -fPIC -c dcel.c -o $(out-o)/dcel.o

dcel-svc:
	gcc $(dbugopts) -fPIC -c dcel_svc.c -o $(out-o)/dcel_svc.o

dcel-child:
	gcc $(dbugopts) -fPIC -c dcel_child.c -o $(out-o)/dcel_child.o

dcel-dirsvc:
	gcc $(dbugopts) -c dcel_dirsvc.c -o $(out-o)/dcel_dirsvc.o

dcel-mapsvc:
	gcc $(dbugopts) -c dcel_mapsvc.c -o $(out-o)/dcel_mapsvc.o

dcel-test: dcel frag ptr-stack mfrag #btree_cpp
	gcc $(dbugopts) $(out-o)/{dcel,frag,ptr_stack,btree_cpp,mfrag}.o dcel_test.c -o $(out-test-bin)/dcel-test -lstdc++



frag:   mfrag
	gcc $(dbugopts) -fPIC -c frag.c -o $(out-o)/frag.o

frag-fh:
	gcc $(dbugopts) -fPIC -c frag_fh.c -o $(out-o)/frag_fh.o

frag-curs: frag-fh frag-svc
	gcc $(dbugopts) -fPIC -c frag_curs.c -o $(out-o)/frag_curs.o

frag-svc:
	gcc $(dbugopts) -fPIC -c frag_svc.c -o $(out-o)/frag_svc.o

fraglib: frag frag-fh frag-svc

fraglibo = frag{,_fh,_svc}.o




map-anchor:
	gcc $(dbugopts) -c map_anchor.c -o $(out-o)/map_anchor.o





mapcel:
	gcc $(dbugopts) -c mapcel.c -o $(out-o)/mapcel.o

mapcel-dir:
	gcc $(dbugopts) -c mapcel_dir.c -o $(out-o)/mapcel_dir.o

mapcel-svc:
	gcc $(dbugopts) -c mapcel_svc.c -o $(out-o)/mapcel_svc.o

mapcel-fh:
	gcc $(dbugopts) -c mapcel_fh.c -o $(out-o)/mapcel_fh.o



mfrag:
	gcc $(dbugopts) -fPIC -c mfrag.c -o $(out-o)/mfrag.o

mfrag-fh:
	gcc $(dbugopts) -fPIC -c mfrag_fh.c -o $(out-o)/mfrag_fh.o

mfrag-svc:
	gcc $(dbugopts) -fPIC -c mfrag_svc.c -o $(out-o)/mfrag_svc.o

mfraglib: mfrag mfrag-fh mfrag-svc

mfraglibo = mfrag{,_fh,_svc}.o



ptr-stack:
	gcc $(dbugopts) -fPIC -c ptr_stack.c -o $(out-o)/ptr_stack.o

test-ptr-stack:
	gcc $(dbugopts) ptr_stack.c test_ptr_stack.c -o $(out-test-bin)/ptr_stack_test

## END ##
