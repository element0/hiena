SHELL = /bin/bash

out-o = ../out/o
out-bin = ../out/bin
out-lib = ../out/lib
out-modules = $(out-lib)/modules
out-test-bin = ../out/test-bin

install-lib = ~/.cosm/lib
install-lib-modules = $(install-lib)/cosmos/modules

src-modules = ./modules

dbugopts = -g
warnopts = -Wall

devlib = ../out/lib 


out-dirs:
	mkdir -p $(out-o)
	mkdir -p $(out-bin)
	mkdir -p $(out-lib)
	mkdir -p $(out-modules)
	mkdir -p $(out-test-bin)

install-dirs:
	mkdir -p $(install-lib)
	mkdir -p $(install-lib-modules)


all: out-dirs install-dirs tests utils


devdirs:  out-dirs


access-frame:
	gcc $(dbugopts) -fPIC -c access_frame.c -o $(out-o)/access_frame.o


btrees:
	gcc $(dbugopts) -c btree.c -o $(out-o)/btree.o
	gcc $(dbugopts) -c btrees.c -o $(out-o)/btrees.o

btree_cpp:
	g++ $(dbugopts) -fPIC -c -std=c++0x btree_cpp.cc -o $(out-o)/btree_cpp.o


cosmos-bind:
	gcc $(dbugopts)  -c cosmos/cosmos_bind.c -o $(out-o)/cosmos_bind.o


cosmos-config:
	gcc $(dbugopts)  -c cosmos/cosmos_config.c -o $(out-o)/cosmos_config.o

cosmos-db:      btree_cpp hash
	gcc $(dbugopts)  -fPIC -c cosmos/cosmos_db.c -o $(out-o)/cosmos_db.o

cosmos-fs:      cosmos-db access-frame
	gcc $(dbugopts)  -fPIC -c cosmos/cosmos_fs.c -o $(out-o)/cosmos_fs.o

cosmos-dirh:      cosmos-db access-frame
	gcc $(dbugopts)  -c cosmos/cosmos_dirh.c -o $(out-o)/cosmos_dirh.o

cosmos-load-mod:        dcel access-frame
	gcc $(dbugopts)  -c cosmos/load_module.c -o $(out-o)/cosmos_load_module.o

cosmos-module:
	gcc $(dbugopts)  -c cosmos/cosmos_module.c -o $(out-o)/cosmos_module.o

cosmos-init:    cosmos-db cosmos-load-mod
	gcc $(dbugopts)  -c cosmos/cosmos_init.c -o $(out-o)/cosmos_init.o


cosmos-util:    cosmos-db cosmos-init
	gcc $(dbugopts)  $(out-o)/cosmos_init.o cosmos/cosmos_util.c -o $(out-bin)/cosmos

dcel:   ptr-stack frag
	gcc $(dbugopts) -fPIC -c dcel.c -o $(out-o)/dcel.o

dcel-svc:
	gcc $(dbugopts) -fPIC -c dcel_svc.c -o $(out-o)/dcel_svc.o

dcel-child:
	gcc $(dbugopts) -fPIC -c dcel_child.c -o $(out-o)/dcel_child.o

dcel-dirsvc:
	gcc $(dbugopts) -c dcel_dirsvc.c -o $(out-o)/dcel_dirsvc.o

dcel-mapsvc:
	gcc $(dbugopts) -c dcel_mapsvc.c -o $(out-o)/dcel_mapsvc.o


documentation:
	mkdir -p ../doc
	doxygen Doxyfile

doc-clean:
	rm -r ../doc/html
	rm -r ../doc/latex
	rm ../doc/doxygen*

dsource:
	gcc $(dbugopts) -c dsource.c -o $(out-o)/dsource.o




file-module: file-so



file-so:  out-dirs
	gcc -g -shared -fPIC $(src-modules)/file_mod/{file_src.c,file_svc.c,file_module.c} -o $(out-modules)/file.so -L$(out-lib) -lhiena


test-file-mod: file-so
	gcc -g test_file_module.c -o file_module_test -ldl




file-svc:
	gcc $(dbugopts) -c services/file_svc.c -o $(out-o)/file_svc.o





frag:   mfrag
	gcc $(dbugopts) -fPIC -c frag.c -o $(out-o)/frag.o

frag-fh:
	gcc $(dbugopts) -fPIC -c frag_fh.c -o $(out-o)/frag_fh.o

frag-curs: frag-fh frag-svc
	gcc $(dbugopts) -fPIC -c frag_curs.c -o $(out-o)/frag_curs.o

frag-svc:
	gcc $(dbugopts) -fPIC -c frag_svc.c -o $(out-o)/frag_svc.o

fraglib: frag frag-fh frag-svc

fraglibo = frag{,_fh,_svc}.o



hpat:
	gcc $(dbugopts) -c hpat.c -o $(out-o)/hpat.o

hash:
	gcc $(dbugopts) -c hash.c -o $(out-o)/hash.o



lookup-hdl:
	gcc $(dbugopts) -c lookup_hdl.c -o $(out-o)/lookup_hdl.o

lookup-svc:
	gcc $(dbugopts) -c lookup_svc.c -o $(out-o)/lookup_svc.o




lookup-light: hash access-frame btree_cpp cosmos-db cosmos-fs dcel dcel-child frag ptr-stack mfrag
	gcc $(dbugopts) -fPIC -shared $(out-o)/{hash.o,access_frame.o,btree_cpp.o,dcel.o,dcel_child.o,frag.o,ptr_stack.o,mfrag.o} $(out-o)/cosmos_{db,fs}.o modules/lookup/light/lookup_light.c -o $(out-lib)/modules/lookup-light.so -lstdc++



libcosmos:  devdirs access-frame cosmos-config cosmos-db cosmos-fs cosmos-module cosmos-init
	gcc $(dbugopts) -fPIC -shared $(out-o)/{access_frame,cosmos_config,cosmos_db,cosmos_fs,cosmos_module}.o -o $(out-lib)/libcosmos.so




libhiena:  devdirs fraglib mfraglib
	gcc $(dbugopts) -shared $(out-o)/$(fraglibo) $(out-o)/$(mfraglibo) -o $(out-lib)/libhiena.so





map-anchor:
	gcc $(dbugopts) -c map_anchor.c -o $(out-o)/map_anchor.o


mapcel:
	gcc $(dbugopts) -c mapcel.c -o $(out-o)/mapcel.o

mapcel-dir:
	gcc $(dbugopts) -c mapcel_dir.c -o $(out-o)/mapcel_dir.o

mapcel-svc:
	gcc $(dbugopts) -c mapcel_svc.c -o $(out-o)/mapcel_svc.o

mapcel-fh:
	gcc $(dbugopts) -c mapcel_fh.c -o $(out-o)/mapcel_fh.o





mfrag:
	gcc $(dbugopts) -fPIC -c mfrag.c -o $(out-o)/mfrag.o

mfrag-fh:
	gcc $(dbugopts) -fPIC -c mfrag_fh.c -o $(out-o)/mfrag_fh.o

mfrag-svc:
	gcc $(dbugopts) -fPIC -c mfrag_svc.c -o $(out-o)/mfrag_svc.o

mfraglib: mfrag mfrag-fh mfrag-svc

mfraglibo = mfrag{,_fh,_svc}.o



modules:  file-module


install-modules:  install-dirs
	mv $(out-lib)/modules/* $(install-lib-modules)/.





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


prod-fns:
	gcc $(dbugopts) -c prod_fns.c -o $(out-o)/prod_fns.o


ptr-stack:
	gcc $(dbugopts) -fPIC -c ptr_stack.c -o $(out-o)/ptr_stack.o

ptr-stack-test:
	gcc $(dbugopts) ptr_stack.c ptr_stack_test.c -o $(out-test-bin)/ptr_stack_test


scanners: ox-so ox2-so


scanner:
	gcc $(dbugopts) -c scanner.c -o $(out-o)/scanner.o

scanner-hdl:
	gcc $(dbugopts) -c scanner_hdl.c -o $(out-o)/scanner_hdl.o

scanner-svc:
	gcc $(dbugopts) -c scanner_svc.c -o $(out-o)/scanner_svc.o

slib:
	gcc $(dbugopts) -c slib.c -o $(out-o)/slib.o


snafufs:  cosmos-fs cosmos-init
	gcc $(dbugopts) $(out-o)/cosmos_{db,fs,init,load_module}.o $(out-o)/{access_frame.o,btree_cpp.o,dcel.o,frag.o,hash.o,mfrag.o,ptr_stack.o} snafufs.c `pkg-config fuse --cflags --libs` -o $(out-bin)/snafufs -lstdc++ -ldl


hiena-obs: btrees btree_cpp dcel dsource context-frame hash map-anchor mapcel mapcel-dir mapcel-svc mapcel-fh mfrag mfrag-fh mfrag-svc ptr-stack frag frag-fh frag-curs frag-svc dcel-svc dcel-mapsvc

hiena-obs-broken: 

svc-obs: file-svc 


tests: out-dirs test-btrees test-dcel-svc test-file-svc test-hiena-fh test-mapcel test-mfrag test-mfrag-fh test-mfrag-svc test-frag test-frag-fh test-frag-svc


test-dcel-child: hash access-frame btree_cpp cosmos-db cosmos-fs dcel dcel-child frag ptr-stack mfrag
	gcc $(dbugopts) $(out-o)/{hash.o,access_frame.o,btree_cpp.o,dcel.o,dcel_child.o,frag.o,ptr_stack.o,mfrag.o} $(out-o)/cosmos_{db,fs}.o test_dcel_child.c -o $(out-test-bin)/dcel_child_test -lstdc++




test-dcel-dirsvc: hash access-frame btree_cpp cosmos-db cosmos-fs dcel dcel-child frag ptr-stack mfrag dcel-dirsvc
	gcc $(dbugopts) $(out-o)/{hash.o,access_frame.o,btree_cpp.o,dcel.o,dcel_child.o,dcel_dirsvc.o,frag.o,ptr_stack.o,mfrag.o} $(out-o)/cosmos_{db,fs}.o test_dcel_dirsvc.c -o $(out-test-bin)/dcel_dirsvc_test -lstdc++

test-dcel-svc: btrees map-anchor mfrag mfrag-fh mfrag-svc frag frag-fh frag-curs frag-svc dcel-svc
	gcc $(dbugopts) $(out-o)/{btree.o,btrees.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o} dcel_svc_test.c -o $(out-test-bin)/dcel_svc_test



test-builtins: libcosmos
	gcc $(dbugopts) test_builtins.c -o $(out-test-bin)/builtins_test -L$(out-lib) -lhiena



test-btrees: btrees
	gcc $(dbugopts) btree.o btrees.o btrees_test.c -o $(out-test-bin)/btrees_test

test-cpp-btree:
	g++ $(dbugopts) -std=c++0x test_cpp_btree.cc -o $(out-test-bin)/cpp_btree_test


test-cpp-btree-c: btree_cpp
	gcc $(dbugopts) $(out-o)/btree_cpp.o test_cpp_btree.c -o $(out-test-bin)/cpp_btree_test -lstdc++




test-cosmos-fs: cosmos-fs
	gcc $(dbugopts) $(out-o)/cosmos_{db,fs}.o $(out-o)/{hash,btree_cpp,access_frame}.o cosmos/cosmos_fs_test.c -o $(out-test-bin)/cosmos_fs_test -lstdc++


test-cosmos-mknodpath: libhiena cosmos-db cosmos-config cosmos-module ptr-stack cosmos-fs dcel cosmos-init cosmos-bind
	gcc $(dbugopts) $(out-o)/cosmos_{db,fs,config,module,init,bind}.o $(out-o)/{hash,btree_cpp,access_frame,ptr_stack,dcel}.o test_cosmos_mknodpath.c -o $(out-test-bin)/cosmos_mknodpath_test -L$(out-lib) -lhiena -lstdc++ -ldl


test-cosmos-module:  libhiena cosmos-db cosmos-config cosmos-module ptr-stack
	gcc $(dbugopts) $(out-o)/cosmos_{db,config,module}.o $(out-o)/{hash,btree_cpp,dcel,access_frame,ptr_stack}.o cosmos/test_cosmos_module.c -o $(out-test-bin)/cosmos_module_test -L$(out-lib) -lhiena -lstdc++



test-file-svc:
	gcc $(dbugopts) hiena_svc.c test_file_svc.c -o $(out-test-bin)/file_svc_test



test-frag:  
	gcc $(dbugopts) btree.c btrees.c mfrag.c frag.c frag_test.c -o $(out-test-bin)/frag_test


test-frag-fh:  
	gcc $(dbugopts) btree.c btrees.c mfrag.c frag.c frag_fh.c frag_fh_test.c -o $(out-test-bin)/frag_fh_test


test-frag-curs:  btrees mfrag mfrag-fh mfrag-svc map-anchor frag frag-fh frag-svc frag-curs
	gcc $(dbugopts) $(out-o)/{btree.o,btrees.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,frag.o,frag_fh.o,frag_svc.o,frag_curs.o} frag_curs_test.c -o $(out-test-bin)/frag_curs_test 


test-frag-svc:
	gcc $(dbugopts) btree.c btrees.c mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c frag_svc_test.c -o $(out-test-bin)/frag_svc_test




test-hiena-fh:
	gcc $(dbugopts) hiena_fh_test.c -o $(out-test-bin)/hiena_fh_test




test-lookup-svc: hash access-frame btree_cpp cosmos-db cosmos-fs dcel dcel-child frag ptr-stack mfrag lookup-svc lookup-hdl prod-fns
	gcc $(dbugopts) $(out-o)/{hash.o,access_frame.o,btree_cpp.o,dcel.o,dcel_child.o,frag.o,ptr_stack.o,mfrag.o,lookup_svc.o,lookup_hdl.o,prod_fns.o} $(out-o)/cosmos_{db,fs}.o test_lookup_svc.c -o $(out-test-bin)/lookup_svc_test -lstdc++

test-mapcel:
	gcc $(dbugopts) btrees.c mapcel.c mapcel_test.c -o $(out-test-bin)/mapcel_test

test-mapcel-dir:
	gcc $(dbugopts) mapcel_dir.c mapcel_dir_test.c -o $(out-test-bin)/mapcel_dir_test


test-mfrag:
	gcc $(dbugopts) mfrag.c mfrag_test.c -o $(out-test-bin)/mfrag_test


test-mfrag-fh:
	gcc $(dbugopts) mfrag_fh.c mfrag_fh_test.c -o $(out-test-bin)/mfrag_fh_test


test-mfrag-svc:
	gcc $(dbugopts) mfrag_fh.c mfrag_svc.c mfrag_svc_test.c -o $(out-test-bin)/mfrag_svc_test


test-prod-fns: prod-fns libhiena
	gcc $(dbugopts) $(out-o)/prod_fns.o test_prod_fns.c -o $(out-test-bin)/prod_fns_test -L$(out-lib) -lhiena 



test_main:  
	gcc $(dbugopts) frag.c frag_test.c test_main.c -o $(out-bin)/test_main




util-hiena-ls: hiena-obs svc-obs slib scanner scanner-hdl
	gcc $(dbugopts) $(out-o)/{btree_cpp.o,context_frame.o,dcel.o,file_svc.o,hash.o,map_anchor.o,mapcel.o,mapcel_dir.o,mapcel_svc.o,mapcel_fh.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,dsource.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o,dcel_mapsvc.o,ptr_stack.o,slib.o,scanner.o,scanner_hdl.o} util/hiena_ls_util.c -o $(out-bin)/hiena-ls -ldl -lstdc++


util-mapalnum: hiena-obs svc-obs
	gcc $(dbugopts) $(out-o)/{btree.o,btrees.o,context_frame.o,dcel.o,file_svc.o,map_anchor.o,mfrag.o,mfrag_fh.o,mfrag_svc.o,dsource.o,frag.o,frag_fh.o,frag_curs.o,frag_svc.o,dcel_svc.o,dcel_mapsvc.o} util/{mapalnum_func.c,mapalnum_util.c} -o $(out-bin)/mapalnum



util-byterange:
	gcc $(dbugopts) hiena_svc.c util/byterange.c -o $(out-bin)/byterange


util-insert-bytes:
	gcc $(dbugopts) mfrag.c mfrag_fh.c mfrag_svc.c frag.c frag_fh.c frag_svc.c file_svc.c util/insert-bytes.c -o $(out-bin)/insert-bytes



utils: util-byterange util-insert-bytes util-hiena-ls


