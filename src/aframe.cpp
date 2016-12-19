#include <iostream>
#include <aframe.hh>
#include <dcel.hh>

int aframe::set_mappers( void * mapperlib )
{
	return 0;
}

void *aframe::get_mappers()
{
	return NULL;
}

aframe::aframe()
{
	cosm = new dcel;
}

aframe::~aframe()
{
	delete cosm;
}
