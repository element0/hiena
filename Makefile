

all: util-insert-bytes

util-byterange:
	gcc service.c service-file.c util/byterange.c -o out/bin/byterange


util-insert-bytes:
	gcc mfrag.c frag.c service-file.c util/insert-bytes.c -o out/bin/insert-bytes


test_main:  
	gcc frag.c frag_test.c test_main.c -o test_main


