#ifndef _HIENA_AFRAME_HH_
#define _HIENA_AFRAME_HH_

#include <dcel.hh>

class aframe {
	void *user;
	void *session;
	void *vhost;
	void *env;
	void *var;
	void *domain;
	dcel *cosm;
    public:
	int   set_mappers( void * );
	void *get_mappers();
	aframe();
	~aframe();
};

#endif /*!_HIENA_AFRAME_HH_*/
