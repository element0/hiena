#include <stdlib.h>
#include "access_frame.h"
#include "cosmos.h"
#include "dcel.h"
#include "hierr.h"
#include "prod_args.h"
#include "prod_types.h"



/*
    convenience functions.  avoids prod instr syntax in the API and hides it during development.

 */

cosmos_id_t prod_src(char *modname, char *addr_str, struct cosmos *cm)
{
        struct access_frame *af;
        cosmos_strid_t modid, label, addr;
        struct prod_args *args;
        struct hiena_dcel *dcel;


        modid = cosmos_put_str(modname);

        label = cosmos_put_str("addr");

        addr = cosmos_put_str(addr_str);


        args = prod_args_new();
        prod_args_add( args, label, PI_STR, (uintptr_t)addr );


        dcel = dcel_new(NULL);
        dcel->prodfn_id = PCMD_SRC;
        dcel->module_id = modid;
        dcel->args = args;

        af = aframe_new();
        af->dcel = dcel;

        return af;
}


 

cosmos_id_t prod_map(cosmos_id_t targ, char *modname, struct cosmos *cm)
{
        cosmos_id_t res, fnframe;
        char *fnpath;


        fnpath = cosmos_calc_fnpath(cm, modname, "cosmos_map_fn");



        /* WIP  headers OK
                implem. WIP */


        fnframe = cosmos_lookup(cm, targ, fnpath);

        res = cosmos_exec(cm, fnframe, targ, 0, NULL);



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



cosmos_id_t prod_transform(cosmos_id_t targ, char *modname, struct prod_args *args, struct cosmos *cm)
{
        char *fnpath;
        cosmos_id_t fnframe, res;

        fnpath = cosmos_calc_fnpath(cm, modname, "cosmos_transform_fn");

        fnframe = cosmos_lookup(cm, targ, fnpath);

        res = cosmos_exec(cm, fnframe, targ, args->argc, args->argv);

        return res;
}

