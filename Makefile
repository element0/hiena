
all: libhiena tests

tests: tests/*_test.c
	gcc -g -Wall tests/*_test.c src/testrun.c -o out/bin/testrun

libhiena:  src/*.c
	gcc -fPIC -g -c -Wall src/*.c -o src/*.o
	gcc -shared -fPIC -Wl,-soname,libhiena.so.1src \
		-o out/lib/libhiena.so.1.0.1 src/hiena.o -lc
