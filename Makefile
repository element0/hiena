

all: out-dirs test-file-svc

broken: util-byterange util-insert-bytes

out-dirs:
	mkdir -p out/{bin,test-bin}

test-file-svc:
	gcc hiena_svc.c file_svc.c file_svc_test.c -o out/test-bin/test-file-svc

util-byterange:
	gcc hiena_svc.c file_svc.c util/byterange.c -o out/bin/byterange


util-insert-bytes:
	gcc mfrag.c frag.c service.c service-file.c util/insert-bytes.c -o out/bin/insert-bytes


test_main:  
	gcc frag.c frag_test.c test_main.c -o test_main


