#include "service.h"
#include <string.h>


struct hiena_svc_module *service_file_new()
{
        struct hiena_svc_module *hsm = new_hiena_svc_module();

	if( hsm == NULL ) return NULL;

	hsm->read  = (size_t (*)( void *, size_t, size_t, void *))fread;

	hsm->write = (size_t (*)( const void *, size_t, size_t, void *))fwrite;

	hsm->open  = (void * (*)( void *, const char *))fopen;

	hsm->close = (int    (*)( void * ))fclose;

	hsm->seek  = (int    (*)( void *, long, int ))fseek; 

	return hsm;
}

int service_file_cleanup(struct hiena_svc_module *hsm)
{
        if( hsm == NULL )
                return-1;

        hiena_svc_module_cleanup( hsm );

        return 0;
}

struct hiena_svc_addr *service_file_addr_new( char *pathname )
{
        if( pathname == NULL ) return NULL;

        struct hiena_svc_addr *addr = new_hiena_svc_addr();

        addr->size = strlen( pathname )*sizeof(char);
        addr->buf  = strndup( pathname, addr->size );

        return addr;
}

void service_file_addr_cleanup( struct hiena_svc_addr  *hsa )
{
        if( hsa != NULL )
        {
                if( hsa->buf != NULL ) free( hsa->buf );
                hiena_svc_addr_cleanup( hsa );
        }
}
