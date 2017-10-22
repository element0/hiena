
#include <stdlib.h>
#include "dcel.h"
#include "lookup_hdl.h"
#include "hierr.h"
#include "dfind.h"
#include "slib.h"
#include "scanner.h"


struct lookup_hdl *lookup_module_init( struct hiena_dcel *dc, struct hiena_slib *slib )
{
        struct lookup_hdl *h;

        h = lookup_hdl_init( dc, slib );

        return h;
}


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

struct hiena_dcel *lookup_find_child( struct lookup_hdl *h, char *s )
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


struct hiena_dcel *lookup_find_prop( struct lookup_hdl *h, char *s )
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

struct hiena_dcel *lookup_grind( struct lookup_hdl *h, char *sn )
{
        if( h == NULL )
        {
                HIERR("lookup_find_child: err: h NULL");
                return NULL;
        }

        struct prod_instr *pi;
        struct hiena_dcel *dc;
        struct hiena_slib *slib;
        struct hiena_scanner *hs;
        struct hiena_dcel *res;

        pi = prod_instr_new();
        dc = h->target;
        slib = h->scanlib;
        hs = slib_get_scanner(sn,slib);

        pi->fn = dgrind;
        pi->argc = 3;
        pi->argv[0] = slib;
        pi->argv[1] = sn;
        pi->argv[2] = dc;

        res = prod_exec( pi );
        
        return res;
}