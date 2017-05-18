

#include "frag_fh.h"
#include <stdlib.h>
#include <string.h>


struct frag_fh *frag_fh_new()
{
        struct frag_fh *fh;

        fh = malloc( sizeof( *fh ));
        memset( fh, 0, sizeof( *fh ));

        return fh;
}

int frag_fh_cleanup( struct frag_fh *fh )
{
        if( fh == NULL )
                return 0;
        
        free( fh );

        return 0;
}