SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .l .y .c .o .so

ox.so:
	bison -Wnone -d ox.y
	flex -o ox.yy.c ox.l
	gcc -c -fPIC ox.tab.c ox.yy.c
	gcc -shared -o ox.so ox.tab.o ox.yy.o
#../../src/libhiena.o

ox:	ox.l ox.y
	bison -d ox.y
	flex -o ox.yy.c ox.l
	gcc -o ox ox.tab.c ox.yy.c

ox-tester:    ox-tester.c ox.so ../../src/libhiena.c
	gcc -rdynamic -o ox-tester ox-tester.c -ldl

.PHONY:	clean install
clean:
	-rm ox.yy.[co] ox.tab.[cho]

libdir = /usr/local/lib/cosmos/_cosm/types
install: ox.so
	mkdir -p $(libdir);
	cp -a ./ox.so $(libdir)/.
