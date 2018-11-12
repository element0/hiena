


file-so:
	gcc -g -shared -fPIC file_svc.c file_module.c -o file.so -L../../../out/lib/libhiena.so


test-file-mod: file-so
	gcc -g test_file_module.c -o file_module_test -ldl