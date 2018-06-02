SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .l .y .c .o .so

ox4.so:
	bison -Wnone -d ox.y
	flex -o ox.yy.c ox.l
	gcc -g -c -fPIC ox.tab.c ox.yy.c
	gcc -g -shared -o ox4.so ox.tab.o ox.yy.o
	-rm ox.yy.[o] ox.tab.[o]
	mv ox4.so ../../../out/lib/scanners/.

ox:	ox.l ox.y
	bison -d ox.y
	flex -o ox.yy.c ox.l
	gcc -g -o ox ox.tab.c ox.yy.c

ox-tester:    ox-tester.c ox.so ../../src/libhiena.c
	gcc -g -rdynamic -o ox-tester ox-tester.c -ldl

.PHONY:	clean install
clean:
	-rm ox.yy.[co] ox.tab.[cho]

libdir = /usr/local/lib/cosmos/_cosm/types

install: ox4.so
	mkdir -p $(libdir);
	cp -a ./ox3.so $(libdir)/.
