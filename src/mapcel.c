#include <stdlib.h>
#include "mapcel.h"
#include "hierr.h"

struct hiena_mapcel *mapcel_new(int ruleid, size_t len)
{
        struct hiena_mapcel *mc;

        mc = malloc(sizeof(*mc));
        if(mc == NULL)
        {
                HIERR("mapcel_new: malloc NULL");
                return NULL;
        }
        mc->len = len;
        mc->ruleid = ruleid;

        return mc;
}

int mapcel_cleanup( struct hiena_mapcel *mc )
{
        if( mc == NULL )
        {
                HIERR("mapcel_cleanup: input mc NULL");
                return -1;
        }

        free(mc);
        return 0;
        
}