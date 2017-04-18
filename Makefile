

all: insert-bytes-util

byterange-util:
	gcc service.c service-file.c util/byterange.c -o out/bin/byterange


insert-bytes-util:
	gcc mfrag.c frag.c util/insert-bytes.c -o out/bin/insert-bytes


test_main:  
	gcc frag.c frag_test.c test_main.c -o test_main


