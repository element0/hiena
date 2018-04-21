
#include "dcel.h"
#include "lookup_hdl.h"
#include "slib.h"



struct lookup_hdl *lookup_module_init( struct hiena_dcel *dc, struct hiena_slib *slib )
{
        struct lookup_hdl *h;

        h = lookup_hdl_init( dc, slib );

        return h;
}
