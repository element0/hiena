#include "hiena_fh.h"
#include "hiena_svc.h"

struct hiena_fh *hiena_fh_new()
{
        struct hiena_fh *fh;

        fh = malloc( sizeof( *fh ));
        memset( fh, 0, sizeof( *fh ));

        return fh;
}

int hiena_fh_cleanup( struct hiena_fh *fh )
{
        if( fh == NULL )
                return 0;

        free( fh );

        return 0;
}
