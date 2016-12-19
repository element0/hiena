#include <iostream>

#include <dcel.hh>
#include <hiena.hh>
#include <aframe.hh>

int main( int argc, char * argv[] )
{
	/* modlib proto */

	dcel * modlib	= new dcel;
	dcel * dirmod	= new dcel;
	dcel * filemod	= new dcel;
	dcel * bufmod	= new dcel;

	aframe *a = new aframe;
	delete a;

	delete modlib;
	delete dirmod;
	delete filemod;
	delete bufmod;

	return 0;
}
