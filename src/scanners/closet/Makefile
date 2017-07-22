
skeleton.so:	skeleton.l skeleton.y
	bison -d skeleton.y
	flex -o skeleton.yy.c skeleton.l
	gcc -c -fPIC skeleton.tab.c skeleton.yy.c
	gcc -shared -o skeleton.so skeleton.tab.o skeleton.yy.o

skeleton-tester:    skeleton-tester.c
	gcc -rdynamic -o skeleton-tester skeleton-tester.c -ldl
