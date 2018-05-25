#include <stdlib.h>
#include "dcel.h"
#include "access_frame.h"
#include "cosmos.h"
#include "hierr.h"



/*
    convenience functions.  avoids prod instr syntax in the API and hides it during development.

 */

cosmos_id_t prod_src(char *modname, char *addr, struct cosmos *)
{

        prod_mod_t mod;
        struct access_frame *af;

        mod = cosmos_db_get_mod(cm, modname);

        af->dcel = mod->source(addr);

        return af;
}
 

cosmos_id_t prod_map(cosmos_id_t, char *, struct cosmos *);
cosmos_id_t prod_map(cosmos_id_t targ, char *modname, struct cosmos *cm)
{
        mod = cosmos_db_get_mod(cm, modname);

        af->dcel = mod->map(targ,cm);

        return af;
}







cosmos_id_t prod_find_child(cosmos_id_t par, char *name, struct cosmos *cm)
{
        (struct access_frame *)par;
        struct hiena_dcel *dc, *dc2;
        struct access_frame *af;



        if(par == COSMOS_ID_NULL)
        {
                HIERR("prod_find_child: err: par NULL");
                return COSMOS_ID_NULL;
        }

        if(cm == COSMOS_ID_NULL)
        {
                HIERR("prod_find_child: err: cm NULL");
                return COSMOS_ID_NULL;
        }




        dc = par->dcel;
        dc2 = dcel_find_child(dc, name, cm);
        af = aframe_new();
        af->dcel = dc2;
     
        return (cosmos_id_t)af;
}



cosmos_id_t prod_find_prop(cosmos_id_t par, char *name, struct cosmos *cm)
{
        return COSMOS_ID_NULL;
}



cosmos_id_t prod_transform(cosmos_id_t targ, char *modname, struct cosmos *cm)
{
        return COSMOS_ID_NULL;
}

