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
        struct access_frame *af;

        modid = cosmos_put_str(modname);

        args;

        prod_args_add( args, "addr", PI_STR, addr );

        dcel->prodfn_id = PCMD_SRC;
        dcel->module_id = modid;
        dcel->args = args;

        af = aframe_new();
        af->dcel = dcel;

        return af;
}


 

cosmos_id_t prod_map(cosmos_id_t targ, char *modname, struct cosmos *cm)
{
        /* WIP */

        fnpath = cosmos_calc_fnpath(cm, modname, "cosmos_map_fn");

        fnframe = cosmos_lookup(cm, targ, fnpath);

        res = cosmos_exec(cm, fnframe, targ, NULL);

        return res;
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



cosmos_id_t prod_transform(cosmos_id_t targ, char *modname, prod_args_t *args, struct cosmos *cm)
{
        /* WIP */

        fnpath = modules_calc_fnpath(cm, targ, modname, "cosmos_map_fn");

        fnframe = cosmos_lookup(cm, targ, fnpath);

        res = cosmos_exec(cm, fnframe, targ, args);

        return res;
}

