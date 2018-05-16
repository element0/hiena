

#include <stdlib.h>
#include <string.h>

#include "lookup_module.h"
#include "lookup_hdl.h"
#include "dcel.h"
#include "slib.h"
#include "hierr.h"



struct lookup_hdl *lookup_hdl_new()
{
        struct lookup_hdl *h;

        h = malloc(sizeof(*h));
        memset(h,0,sizeof(*h));

        return h;
}


int lookup_hdl_init( struct lookup_hdl *h, struct hiena_dcel *dc, struct hiena_slib *slib )
{
        if( h == NULL )
        {
                 HIERR("lookup_hdl_init: err: h NULL");
                return -1;
        }

        if( slib == NULL )
        {
                 HIERR("lookup_hdl_init: err: slib NULL");
                return -1;
        }

        h->target = dc;
        h->scanlib = slib;

        h->set_target = lookup_set_target;

        h->find_child = lookup_find_child;

        h->find_prop = lookup_find_prop;

        h->grind = lookup_grind;

        return 0;
}


int lookup_hdl_cleanup(struct lookup_hdl *h)
{
        if( h == NULL )
        {
                HIERR("lookup_hdl_cleanup: err: h NULL");
                return -1;
        }
        free(h);

        return 0;
}
