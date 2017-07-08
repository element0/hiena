out-o = ../out/o
out-bin = ../out/bin
out-test-bin = ../out/test-bin

all: out-dirs tests utils

utils: util-byterange util-insert-bytes

out-dirs:
	mkdir -p $(out-o)
	mkdir -p $(out-bin)
	mkdir -p $(out-test-bin)


btrees:
	gcc -c btree.c -o $(out-o)/btree.o
	gcc -c btrees.c -o $(out-o)/btrees.o

map-anchor:
	gcc -c map_anchor.c -o $(out-o)/map_anchor.o

mfrag:
	gcc -c mfrag.c -o $(out-o)/mfrag.o

mfrag-fh:
	gcc -c mfrag_fh.c -o $(out-o)/mfrag_fh.o

mfrag-svc:
	gcc -c mfrag_svc.c -o $(out-o)/mfrag_svc.o

frag:
	gcc -c frag.c -o $(out-o)/frag.o

frag-fh:
	gcc -c frag_fh.c -o $(out-o)/frag_fh.o

frag-curs: frag-fh frag-svc
	gcc -c frag_curs.c -o $(out-o)/frag_curs.o

frag-svc:
	gcc -c frag_svc.c -o $(out-o)/frag_svc.o

dcel-svc:
	gcc -c dcel_svc.c -o $(out-o)/dcel_svc.o


hiena-obs: btrees map-anchor mfrag mfrag-fh mfrag-svc frag frag-fh frag-curs frag-svc dcel-svc

tests: out-dirs test-btrees test-dcel-svc test-file-svc test-hiena-fh test-mapcel test-mfrag test-mfrag-fh test-mfrag-svc test-frag test-frag-fh test-frag-svc


test-dcel-svc: btrees map-anchor mfrag mfrag-fh mfrag-svc frag frag-fh frag-curs frag-svc dcel-svc
	gcc $(out-o)/{btree.o,btrees.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o} dcel_svc_test.c -o $(out-test-bin)/dcel_svc_test


test-btrees: btrees
	gcc btree.o btrees.o btrees_test.c -o $(out-test-bin)/btrees_test

test-file-svc:
	gcc hiena_svc.c file_svc_test.c -o $(out-test-bin)/file_svc_test


test-hiena-fh:
	gcc hiena_fh_test.c -o $(out-test-bin)/hiena_fh_test


test-frag:  
	gcc btree.c btrees.c mfrag.c frag.c frag_test.c -o $(out-test-bin)/frag_test


test-frag-fh:  
	gcc btree.c btrees.c mfrag.c frag.c frag_fh.c frag_fh_test.c -o $(out-test-bin)/frag_fh_test


test-frag-curs:  btrees mfrag mfrag-fh mfrag-svc map-anchor frag frag-fh frag-svc frag-curs
	gcc $(out-o)/{btree.o,btrees.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,frag.o,frag_fh.o,frag_svc.o,frag_curs.o} frag_curs_test.c -o $(out-test-bin)/frag_curs_test


test-frag-svc:
	gcc btree.c btrees.c mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c frag_svc_test.c -o $(out-test-bin)/frag_svc_test

test-mapcel:
	gcc btrees.c mapcel.c mapcel_test.c -o $(out-test-bin)/mapcel_test

test-mfrag:
	gcc mfrag.c mfrag_test.c -o $(out-test-bin)/mfrag_test


test-mfrag-fh:
	gcc mfrag_fh.c mfrag_fh_test.c -o $(out-test-bin)/mfrag_fh_test


test-mfrag-svc:
	gcc mfrag_fh.c mfrag_svc.c mfrag_svc_test.c -o $(out-test-bin)/mfrag_svc_test




util-mapalnum: hiena-obs
	gcc $(out-o)/{btree.o,btrees.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o} util/{mapalnum_func.c,mapalnum_util.c} -o $(out-bin)/mapalnum



util-byterange:
	gcc hiena_svc.c util/byterange.c -o $(out-bin)/byterange


util-insert-bytes:
	gcc mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c file_svc.c util/insert-bytes.c -o $(out-bin)/insert-bytes


test_main:  
	gcc frag.c frag_test.c test_main.c -o $(out-bin)/test_main


