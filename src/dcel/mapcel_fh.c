


#include <stdlib.h>
#include <string.h>
#include "mapcel_fh.h"
#include "hierr.h"



struct mapcel_fh *mapcel_fh_new()
{
        struct mapcel_fh *h;

        h = malloc(sizeof(*h));
        memset(h,0,sizeof(*h));

        return h;
}

int mapcel_fh_cleanup( struct mapcel_fh *h )
{
        if(h == NULL)
        {
                HIERR("mapcel_fh_cleanup: warning: input h NULL");
                return -1;
        }

        free(h);

        return 0;
}