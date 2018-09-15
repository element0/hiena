









out-test-bin = ../../out/test-bin

vfnbank:  
	gcc -g -shared -Wl,-soname,vfnbank.so.1 -fPIC vfnbank.c -o $(out-test-bin)/vfnbank.so


vfnbank2:  
	gcc -g -shared -Wl,-soname,vfnbank.so.2 -fPIC vfnbank.c -o $(out-test-bin)/vfnbank2.so


test_vfnbank:   vfnbank vfnbank2
	gcc -g test_vfnbank.c -o $(out-test-bin)/vfnbank_test -ldl