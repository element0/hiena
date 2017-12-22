

#include <stdlib.h>
#include "access_frame.h"
#include "hierr.h"


struct access_frame *access_frame_init()
{
        struct access_frame *af;

        af = malloc(sizeof(*af));

        return af;
}


int access_frame_cleanup( struct access_frame *af )
{
        if( af == NULL )
        {
                HIERR("access_frame_cleanup called on a NULL ptr");
                return -1;
        }
        free( af );

        return 0;
}