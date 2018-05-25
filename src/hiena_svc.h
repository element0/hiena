#ifndef HIENA_SERVICE_H
#define HIENA_SERVICE_H

#include <stdio.h>
#include <stdlib.h>

struct hiena_svc
{
        void *(*source)( void *addr, void *cosmos_db );
        void *(*map)( void *target, void *cosmos_db );
        void *(*transform)( void *target, void *cosmos_db );
        void * (*open)( void *addr, const char *mode);
        int    (*close)( void *fp );
        int    (*seek)( void *fp, long offset, int whence );
        size_t (*read)( void *ptr, size_t size, size_t nmemb, void *fp );
	size_t (*write)( void *ptr, size_t size, size_t nmemb, void *fp );
       int (*getchar)( void * );
};


/* a database item */


struct svc_item {
        void *dl;
        struct hiena_svc *svc;
};

struct svc_item *svc_item_new( void *dl );





#endif /*!HIENA_SERVICE_H*/
