
#include "../../../cosmos.h"
#include "../../../access_frame.h"
#include "../../../dcel.h"
#include "../../../hierr.h"


struct access_frame *cosmos_lookup_fn( struct cosmos *cm, struct access_frame *par, char *s )
{
        struct hiena_dcel *dc, *res;
        struct access_frame *resaf;

        dc = par->dcel;
        res = dcel_find_child(dc, s, cm);

        if( res == NULL )
        {
                HIERR("lookup_light: cosmos_lookup_fn: res NULL");

                return NULL;
        }

        resaf = aframe_spawn(par);
        if( resaf == NULL )
        {
                HIERR("lookup_light: cosmos_lookup_fn: resaf NULL");

                return NULL;
        }


        resaf->dcel = res;

        return resaf;
}
