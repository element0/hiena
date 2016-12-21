
all: test_hiena

deps: dep/dcel/src/*
	$(MAKE) -C dep/dcel/

test_hiena: deps srccpp modules tests/test_hiena.cpp
	g++ -g -Wall tests/test_hiena.cpp \
	dep/dcel/src/dcel.oo \
	src/hiena.oo \
	src/aframe.oo \
	module/file/service.oo \
	-Idep/dcel/src/ \
	-Isrc/ \
	-o tests/test_hienapp

srccpp:	src/*cpp src/*hh
	g++ -g -Wall -c src/aframe.cpp \
	-Isrc/ -Idep/dcel/src/ \
	-o src/aframe.oo
	g++ -g -Wall -c src/hiena.cpp \
	-Isrc/ -Idep/dcel/src/ \
	-o src/hiena.oo

filemod: module/file/service.cpp
	g++ -g -Wall -c module/file/service.cpp \
	-Isrc/ -Idep/dcel/src/ \
	-o module/file/service.oo -std=c++11

modules: filemod

libhiena:  src/*.c
	gcc -shared -fPIC -Wl,-soname,libhiena.so.1src \
	    -o out/lib/libhiena.so.1.0.1 src/hiena.o -lc
