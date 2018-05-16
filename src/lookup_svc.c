
#include <stdlib.h>
#include "dcel.h"
#include "lookup_hdl.h"
#include "hierr.h"
#include "prod_fns.h"



int lookup_set_target( struct lookup_hdl *h, lookup_target_t *targ )
{
        if( h == NULL )
        {
                HIERR("lookup_set_target: err: h NULL");
                return -1;
        }

        h->target = targ;

        return 0;
}

lookup_target_t *lookup_find_child( struct lookup_hdl *h, char *name )
{
        if( h == NULL )
        {
                HIERR("lookup_find_child: err: h NULL");
                return NULL;
        }



        cosmos_id_t par;
        struct cosmos *cm;
        struct access_frame *res;


        par = (cosmos_id_t)(h->target);
        cm = h->cosmos;


        res = (struct access_frame *)prod_find_child(par,name,cm);

        return res;
}


lookup_target_t *lookup_find_prop( struct lookup_hdl *h, char *name )
{
        if( h == NULL )
        {
                HIERR("lookup_find_child: err: h NULL");
                return NULL;
        }


        cosmos_id_t par;
        struct cosmos *cm;
        struct access_frame *res;


        par = (cosmos_id_t)(h->target);
        cm = h->cosmos;


        res = (struct access_frame *)prod_find_prop(par,name,cm);


        
        return res;
}

lookup_target_t *lookup_transform( struct lookup_hdl *look, char *str )
{

        struct cosmos *cm;
        cosmos_id_t res, cur;


        if( look == NULL )
        {
                HIERR("lookup_transform: err: lookup handle NULL");
                return NULL;
        }

        cm = look->cosmos;

        if( cm == NULL )
        {
                HIERR("lookup_transform: err: cm NULL");
                return NULL;
        }



        res = prod_map( cur, str, cm );

        if( res == COSMOS_ID_NULL )
        {
                res = prod_transform( cur, str, cm );
        }

        if( res == COSMOS_ID_NULL )
        {
                HIERR("lookup_transform: err: prod_exec can't map or transform.");
                return NULL;
        }

        return res; 
}
