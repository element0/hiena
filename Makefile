

byterange-util:
	gcc service.c service-file.c util/stitch.c -o util/stitch

frag_test:  
	gcc frag.c frag_test.c test_main.c -o test_main

