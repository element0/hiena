





#include <stdlib.h>
#include "map_anchor.h"


struct map_anchor *map_anchor_new()
{
        struct map_anchor *ma;

        ma = malloc(sizeof(*ma));

        return ma;
}

int map_anchor_cleanup( struct map_anchor *ma )
{
        if( ma == NULL )
		return -1;

	free( ma );

	return 0;
}
