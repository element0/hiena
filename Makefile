

byterange-util:
	gcc service.c service-file.c util/byterange.c -o util/byterange

frag_test:  
	gcc frag.c frag_test.c test_main.c -o test_main

