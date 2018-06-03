SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .l .y .c .o .so

fudge:
	bison -Wnone -d fudge.y
	flex -o fudge.yy.c fudge.l
	gcc -g -c -fPIC fudge.yy.c fudge.tab.c
	gcc -g -shared -o fudge.so fudge.tab.o fudge.yy.o
	-rm fudge.yy.[o] fudge.tab.[o]
	mv fudge.so ../../../../out/lib/modules/.

fudge-c:
	bison -Wnone -d fudge.y
	flex -o fudge.yy.c fudge.l

skip:
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
