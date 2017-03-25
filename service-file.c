#include "service.h"


int service_file_init( struct hiena_svc_module *hsm )
{
	if( hsm == NULL ) return -1;

	hsm->read  = (size_t (*)( void *, size_t, size_t, void *))fread;
	hsm->write = (size_t (*)( const void *, size_t, size_t, void *))fwrite;
	hsm->open  = (void * (*)( const char *, const char *))fopen;
	hsm->close = (int    (*)( void * ))fclose;
	hsm->seek  = (int    (*)( void *, long, int ))fseek; 

	return 0;
}
