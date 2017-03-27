#ifndef HIENA_SERVICE_H
#define HIENA_SERVICE_H

#include <stdio.h>
#include <stdlib.h>


struct hiena_svc_module
{
	void * (*open)( void *addr, const char *mode);
	int    (*close)( void *fp );
	int    (*seek)( void *fp, long offset, int whence );
	size_t (*read)( void *ptr, size_t size, size_t nmemb, void *fp );
	size_t (*write)( const void *ptr, size_t size, size_t nmemb, void *fp );
};

struct hiena_svc_addr
{
	void *buf;
	size_t size;
};

struct hiena_io_handle
{
	struct hiena_svc_module *svc;
	struct hiena_svc_addr   *addr;
	off_t pos;
};

struct hiena_svc_module *new_hiena_svc_module ();

struct hiena_svc_addr   *new_hiena_svc_addr ();

void   hiena_svc_module_cleanup( struct hiena_svc_module * );

void   hiena_svc_addr_cleanup( struct hiena_svc_addr * );


#endif /*!HIENA_SERVICE_H*/
