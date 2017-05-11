

all: out-dirs tests util-byterange

broken: util-byterange util-insert-bytes

out-dirs:
	mkdir -p out/bin
	mkdir -p out/test-bin

tests: test-file-svc test-frag test-mfrag test-hiena-fh

test-file-svc:
	gcc hiena_svc.c file_svc_test.c -o out/test-bin/file_svc_test

test-frag:  
	gcc mfrag.c frag.c frag_test.c -o out/test-bin/frag_test

test-mfrag:
	gcc mfrag.c mfrag_test.c -o out/test-bin/mfrag_test

test-hiena-fh:
	gcc hiena_fh_test.c -o out/test-bin/hiena_fh_test

test-frag-fh:  
	gcc frag.c frag_fh.c frag_fh_test.c -o out/test-bin/frag_fh_test


util-byterange:
	gcc hiena_svc.c util/byterange.c -o out/bin/byterange


util-insert-bytes:
	gcc mfrag.c frag.c service.c service-file.c util/insert-bytes.c -o out/bin/insert-bytes


test_main:  
	gcc frag.c frag_test.c test_main.c -o test_main


