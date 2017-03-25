#include "service.h"

struct hiena_svc_module *new_hiena_svc_module ()
{
	struct hiena_svc_module *hsm = malloc(sizeof(*hsm));
	return hsm;
}

void hiena_svc_module_cleanup( struct hiena_svc_module *hsm )
{
	if ( hsm != NULL )
	{
		free( hsm );
	}
}

struct hiena_svc_addr *new_hiena_svc_addr ()
{
	struct hiena_svc_addr *addr = malloc(sizeof(*addr));
	return addr;
}

void hiena_svc_addr_cleanup( struct hiena_svc_addr *addr )
{
	if( addr != NULL )
	{
		free( addr );
	}
}
