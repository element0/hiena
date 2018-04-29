
#include <stdlib.h>
#include "dcel.h"
#include "lookup_hdl.h"
#include "hierr.h"
#include "dfind.h"
#include "slib.h"
#include "scanner.h"




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

lookup_target_t *lookup_find_child( struct lookup_hdl *h, char *s )
{
        if( h == NULL )
        {
                HIERR("lookup_find_child: err: h NULL");
                return NULL;
        }

        struct prod_instr *pi;
        struct hiena_dcel *dc;
        struct hiena_dcel *res;

        pi = prod_instr_new();
        dc = h->target;

        pi->fn = dfind_child;
        pi->argc = 2;
        pi->argv = malloc(sizeof(void *)*2);
        pi->argv[0] = (void *)dc;
        pi->argv[1] = (void *)s;

        res = prod_exec( pi );
        
        return res;
}


lookup_target_t *lookup_find_prop( struct lookup_hdl *h, char *s )
{
        if( h == NULL )
        {
                HIERR("lookup_find_child: err: h NULL");
                return NULL;
        }

        struct prod_instr *pi;
        struct hiena_dcel *dc;
        struct hiena_dcel *res;

        pi = prod_instr_new();
        dc = h->target;

        pi->fn = dfind_prop;
        pi->argc = 2;
        pi->argv = malloc(sizeof(void *)*2);
        pi->argv[0] = (void *)dc;
        pi->argv[1] = (void *)s;

        res = prod_exec( pi );
        
        return res;
}

lookup_target_t *lookup_transform( struct lookup_hdl *look, char *str )
{

        lookup_target_t *res, *cur;


        if( look == NULL )
        {
                HIERR("lookup_transform: err: lookup handle NULL");
                return NULL;
        }

        cm = look->cosmos_db;

        if( cm == NULL )
        {
                HIERR("lookup_transform: err: cm NULL");
                return NULL;
        }



        res = prod_exec( cm, PI_MAP, cur, str );

        if( res == PRODUCTION_ERR )
        {
                res = prod_exec( cm, PI_TRANS, cur, str );
        }

        if( res == PRODUCTION_ERR )
        {
                HIERR("lookup_transform: err: prod_exec can't map or transform.");
                return NULL;
        }

        return res; 
}
