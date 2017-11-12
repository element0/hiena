

#include <stdlib.h>
#include "context_frame.h"
#include "hierr.h"


struct context_frame *context_frame_init()
{
        struct context_frame *cf;

        cf = malloc(sizeof(*cf));

        return cf;
}


int context_frame_cleanup( struct context_frame *cf )
{
        if( cf == NULL )
        {
                HIERR("context_frame_cleanup called on a NULL ptr");
                return -1;
        }
        free( cf );

        return 0;
}