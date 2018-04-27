
#include <stdlib.h>
#include "dcel.h"
#include "lookup_hdl.h"
#include "hierr.h"
#include "dfind.h"
#include "slib.h"
#include "scanner.h"




int lookup_set_target( struct lookup_hdl *h, struct hiena_dcel *dc )
{
        if( h == NULL )
        {
                HIERR("lookup_set_target: err: h NULL");
                return -1;
        }

        h->target = dc;

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


        cosmos_str_id_t strid;

        strid = cosmos_string_put( cm, str );


        listA = look->pilist;
        listB = prod_instr_list_new();
        listC = prod_instr_list_new();
        listD = prod_instr_list_new();

        prod_instr_list_add( listA,
        PI_IFN, listA, listB );

        prod_instr_list_add( listB,
        PI_IFN, listA, listB );

        prod_instr_list_add( listB,
        PI_MAP, PI_STACK, strid );

        prod_instr_list_add( listC,
        PI_TRANS, PI_STACK, strid );


        
        listA = look->pilist;

        prod_instr_list_add( listA,
        PI_IFN, listA, listB );


}
