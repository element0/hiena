#include "dcel.h"
#include "hierr.h"
#include "frag.h"

struct hiena_dcel *dcel_new( struct hiena_dcel *dcgarbage )
{
	return NULL;
}


int dcel_cleanup( struct hiena_dcel *dc )
{
        if( dc == NULL )
        {
                HIERR("dcel_cleanup called on a NULL ptr");
                return -1;
        }

        if( dc->retain > 0 )
        {
                dcel_release( dc );
                return 0;
        }
        frag_cleanup( dc->frag );
        free( dc );

        return 0;
}
