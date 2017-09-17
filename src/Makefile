SHELL = /bin/bash

out-o = ../out/o
out-bin = ../out/bin
out-test-bin = ../out/test-bin

dbugopts = -g


out-dirs:
	mkdir -p $(out-o)
	mkdir -p $(out-bin)
	mkdir -p $(out-test-bin)


all: out-dirs tests utils





btrees:
	gcc $(dbugopts) -c btree.c -o $(out-o)/btree.o
	gcc $(dbugopts) -c btrees.c -o $(out-o)/btrees.o

btree_cpp:
	g++ $(dbugopts) -std=c++0x btree_cpp.cc -o $(out-o)/btree_cpp.o

context-frame:
	gcc $(dbugopts) -c context_frame.c -o $(out-o)/context_frame.o

dcel:
	gcc $(dbugopts) -c dcel.c -o $(out-o)/dcel.o

dcel-svc:
	gcc $(dbugopts) -c dcel_svc.c -o $(out-o)/dcel_svc.o

dcel-mapsvc:
	gcc $(dbugopts) -c dcel_mapsvc.c -o $(out-o)/dcel_mapsvc.o


dsource:
	gcc $(dbugopts) -c dsource.c -o $(out-o)/dsource.o


file-svc:
	gcc $(dbugopts) -c file_svc.c -o $(out-o)/file_svc.o


frag:
	gcc $(dbugopts) -c frag.c -o $(out-o)/frag.o

frag-fh:
	gcc $(dbugopts) -c frag_fh.c -o $(out-o)/frag_fh.o

frag-curs: frag-fh frag-svc
	gcc $(dbugopts) -c frag_curs.c -o $(out-o)/frag_curs.o

frag-svc:
	gcc $(dbugopts) -c frag_svc.c -o $(out-o)/frag_svc.o


hpat:
	gcc $(dbugopts) -c hpat.c -o $(out-o)/hpat.o

hash:
	gcc $(dbugopts) -c hash.c -o $(out-o)/hash.o


map-anchor:
	gcc $(dbugopts) -c map_anchor.c -o $(out-o)/map_anchor.o


mapcel:
	gcc $(dbugopts) -c mapcel.c -o $(out-o)/mapcel.o


mfrag:
	gcc $(dbugopts) -c mfrag.c -o $(out-o)/mfrag.o

mfrag-fh:
	gcc $(dbugopts) -c mfrag_fh.c -o $(out-o)/mfrag_fh.o

mfrag-svc:
	gcc $(dbugopts) -c mfrag_svc.c -o $(out-o)/mfrag_svc.o




ox:
	$(MAKE) -C scanners/ox/

ox2:
	$(MAKE) -C scanners/ox2/

ox3:
	$(MAKE) -C scanners/ox3/

ox4:
	$(MAKE) -C scanners/ox4/


ox-tester:
	gcc -rdynamic -o ox-tester ox-tester.c -ldl

scanners: ox-so ox2-so


scanner:
	gcc $(dbugopts) -c scanner.c -o $(out-o)/scanner.o

scanner-hdl:
	gcc $(dbugopts) -c scanner_hdl.c -o $(out-o)/scanner_hdl.o

scanner-svc:
	gcc $(dbugopts) -c scanner_svc.c -o $(out-o)/scanner_svc.o

slib:
	gcc $(dbugopts) -c slib.c -o $(out-o)/slib.o




hiena-obs: btrees dcel dsource context-frame hash map-anchor mapcel mfrag mfrag-fh mfrag-svc frag frag-fh frag-curs frag-svc dcel-svc dcel-mapsvc

svc-obs: file-svc

tests: out-dirs test-btrees test-dcel-svc test-file-svc test-hiena-fh test-mapcel test-mfrag test-mfrag-fh test-mfrag-svc test-frag test-frag-fh test-frag-svc


test-dcel-svc: btrees map-anchor mfrag mfrag-fh mfrag-svc frag frag-fh frag-curs frag-svc dcel-svc
	gcc $(dbugopts) $(out-o)/{btree.o,btrees.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o} dcel_svc_test.c -o $(out-test-bin)/dcel_svc_test


test-cpp-btree:
	g++ $(dbugopts) -std=c++0x test_cpp_btree.cc -o $(out-test-bin)/cpp_btree_test


test-btrees: btrees
	gcc $(dbugopts) btree.o btrees.o btrees_test.c -o $(out-test-bin)/btrees_test

test-file-svc:
	gcc $(dbugopts) hiena_svc.c file_svc_test.c -o $(out-test-bin)/file_svc_test


test-hiena-fh:
	gcc $(dbugopts) hiena_fh_test.c -o $(out-test-bin)/hiena_fh_test


test-frag:  
	gcc $(dbugopts) btree.c btrees.c mfrag.c frag.c frag_test.c -o $(out-test-bin)/frag_test


test-frag-fh:  
	gcc $(dbugopts) btree.c btrees.c mfrag.c frag.c frag_fh.c frag_fh_test.c -o $(out-test-bin)/frag_fh_test


test-frag-curs:  btrees mfrag mfrag-fh mfrag-svc map-anchor frag frag-fh frag-svc frag-curs
	gcc $(dbugopts) $(out-o)/{btree.o,btrees.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,frag.o,frag_fh.o,frag_svc.o,frag_curs.o} frag_curs_test.c -o $(out-test-bin)/frag_curs_test


test-frag-svc:
	gcc $(dbugopts) btree.c btrees.c mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c frag_svc_test.c -o $(out-test-bin)/frag_svc_test

test-mapcel:
	gcc $(dbugopts) btrees.c mapcel.c mapcel_test.c -o $(out-test-bin)/mapcel_test

test-mfrag:
	gcc $(dbugopts) mfrag.c mfrag_test.c -o $(out-test-bin)/mfrag_test


test-mfrag-fh:
	gcc $(dbugopts) mfrag_fh.c mfrag_fh_test.c -o $(out-test-bin)/mfrag_fh_test


test-mfrag-svc:
	gcc $(dbugopts) mfrag_fh.c mfrag_svc.c mfrag_svc_test.c -o $(out-test-bin)/mfrag_svc_test


test_main:  
	gcc $(dbugopts) frag.c frag_test.c test_main.c -o $(out-bin)/test_main




util-hiena-ls: hiena-obs svc-obs slib scanner scanner-hdl
	gcc $(dbugopts) $(out-o)/{btree.o,btrees.o,context_frame.o,dcel.o,file_svc.o,hash.o,map_anchor.o,mapcel.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,dsource.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o,dcel_mapsvc.o,slib.o,scanner.o,scanner_hdl.o} util/hiena_ls_util.c -o $(out-bin)/hiena-ls -ldl


util-mapalnum: hiena-obs svc-obs
	gcc $(dbugopts) $(out-o)/{btree.o,btrees.o,context_frame.o,dcel.o,file_svc.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,dsource.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o,dcel_mapsvc.o} util/{mapalnum_func.c,mapalnum_util.c} -o $(out-bin)/mapalnum



util-byterange:
	gcc $(dbugopts) hiena_svc.c util/byterange.c -o $(out-bin)/byterange


util-insert-bytes:
	gcc $(dbugopts) mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c file_svc.c util/insert-bytes.c -o $(out-bin)/insert-bytes



utils: util-byterange util-insert-bytes util-hiena-ls


