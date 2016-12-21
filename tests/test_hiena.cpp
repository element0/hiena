#include <iostream>

#include <dcel.hh>
#include <hiena.hh>
#include <aframe.hh>
#include <fileops.hh>
#include "../module/file/service.hh"
#include <cstdlib>
#include <cstdio>

using namespace std;

int main( int argc, char * argv[] )
{
	char *filename = NULL;

	if( argc == 2 ) {
		filename = argv[1];
	}else{
		cout << "please enter a filename";
		return 0;
	}

	/* modlib proto */

	dcel * modlib	= new dcel;
	dcel * dirmod	= new dcel;
	dcel * filemod	= new dcel;
	dcel * bufmod	= new dcel;

	/* test a fileops module */

	fileops *service = hiena_module_init();
	void *fh = service->open( filename, "r" );
	void *buf = malloc(sizeof(char)*1000);
	service->read( buf, sizeof(char), 1000, fh );
	printf("%s", static_cast<char *>(buf));
	free(buf);
	service->close( fh );
	delete service;

	/*  */

	aframe *a = new aframe;
	delete a;


	delete modlib;
	delete dirmod;
	delete filemod;
	delete bufmod;

	return 0;
}
