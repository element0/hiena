#include "hiena_fh.h"
#include "hiena_svc.h"
#include <stdlib.h>
#include <string.h>

struct hiena_svc *hiena_svc_new ()
{
        struct hiena_svc *svc = malloc(sizeof(*svc));

        memset( svc, 0, sizeof( *svc ));

        return svc;
}

void hiena_svc_cleanup( struct hiena_svc *svc )
{
	if ( svc != NULL )
	{
		free( svc );
	}
}

