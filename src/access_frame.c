#include <stdlib.h>
#include <string.h>
#include "access_frame.h"
#include "btree_cpp.h"
#include "hierr.h"


struct access_frame *aframe_new()
{
        struct access_frame *af;

        af = malloc(sizeof(*af));
        memset(af,0,sizeof(*af));

        af->branch = btree_new();

        return af;
}


int aframe_cleanup( struct access_frame *af )
{
        if( af == NULL )
        {
                HIERR("aframe_cleanup called on a NULL ptr");
                return -1;
        }
        btree_cleanup( af->branch );
        free( af );

        return 0;
}
