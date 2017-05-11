#ifndef HIENA_SERVICE_H
#define HIENA_SERVICE_H

#include <stdio.h>
#include <stdlib.h>


struct hiena_svc
{
	void * (*open)( void *addr, const char *mode);
	int    (*close)( void *fp );
	int    (*seek)( void *fp, long offset, int whence );
	size_t (*read)( void *ptr, size_t size, size_t nmemb, void *fp );
	size_t (*write)( const void *ptr, size_t size, size_t nmemb, void *fp );
        int (*getchar)( void * );
};

//---- deprec. ----
struct hiena_svc *hiena_svc_new ();
void   hiena_svc_cleanup( struct hiena_svc * );


#endif /*!HIENA_SERVICE_H*/
