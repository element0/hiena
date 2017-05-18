out-bin = ../out/bin
out-test-bin = ../out/test-bin

all: out-dirs tests utils

utils: util-byterange util-insert-bytes

out-dirs:
	mkdir -p $(out-bin)
	mkdir -p $(out-test-bin)


tests: test-file-svc test-hiena-fh test-mfrag test-mfrag-fh test-mfrag-svc test-frag test-frag-fh test-frag-svc


test-file-svc:
	gcc hiena_svc.c file_svc_test.c -o $(out-test-bin)/file_svc_test


test-hiena-fh:
	gcc hiena_fh_test.c -o $(out-test-bin)/hiena_fh_test


test-frag:  
	gcc mfrag.c frag.c frag_test.c -o $(out-test-bin)/frag_test


test-frag-fh:  
	gcc mfrag.c frag.c frag_fh.c frag_fh_test.c -o $(out-test-bin)/frag_fh_test


test-frag-svc:
	gcc mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c frag_svc_test.c -o $(out-test-bin)/frag_svc_test


test-mfrag:
	gcc mfrag.c mfrag_test.c -o $(out-test-bin)/mfrag_test


test-mfrag-fh:
	gcc mfrag_fh.c mfrag_fh_test.c -o $(out-test-bin)/mfrag_fh_test


test-mfrag-svc:
	gcc mfrag_fh.c mfrag_svc.c mfrag_svc_test.c -o $(out-test-bin)/mfrag_svc_test


util-byterange:
	gcc hiena_svc.c util/byterange.c -o $(out-bin)/byterange


util-insert-bytes:
	gcc mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c file_svc.c util/insert-bytes.c -o $(out-bin)/insert-bytes


test_main:  
	gcc frag.c frag_test.c test_main.c -o $(out-bin)/test_main


