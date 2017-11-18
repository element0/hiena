SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .l .y .c .o .so

cosmosdlang.so:
	bison -Wnone -d cosmosdlang.y
	flex -o cosmosdlang.yy.c cosmosdlang.l
	gcc -g -c -fPIC cosmosdlang.tab.c cosmosdlang.yy.c
	gcc -g -shared -o cosmosdlang.so cosmosdlang.tab.o cosmosdlang.yy.o
	-rm cosmosdlang.yy.[o] cosmosdlang.tab.[o]
	mv cosmosdlang.so ../../../out/lib/lookup/.

cosmosdlang.c:
	bison -Wnone -d cosmosdlang.y
	flex -o cosmosdlang.yy.c cosmosdlang.l


.PHONY:	clean install
clean:
	-rm cosmosdlang.yy.[co] cosmosdlang.tab.[cho]

libdir = /usr/local/lib/cosmos/cosmosd

install: cosmosdlang.so
	mkdir -p $(libdir);
	cp -a ./cosmosdlang.so $(libdir)/.
