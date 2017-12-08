
#include <libgen.h>    // basename()
#include "../hierr.h"
#include "cosmos_db.h"


static void example_init_seq()
{
        struct cosmos *cm;
        int modc = 6;
        char *mod_path[] = {
  "/usr/lib/cosmos",
  "/usr/lib/cosmos/svc/file.so",
  "/usr/lib/cosmos/svc/dylib.so",
  "/usr/lib/cosmos/svc/ptr.so",
  "/usr/lib/cosmos/xformr/dcelcosm.so",
  "/usr/lib/cosmos/lookup/fudge.so",

        };

        cm = cosmos_init( modc,mod_path );

}


struct cosmos *cosmos_init( int modc, char *mod_path[] )
{
        struct cosmos *cm;
        int i;
        cosmos_id_t err;

        char *cosm_path = mod_path[0];

        cm = cosmos_db_new();

        for(i=1; i<modc; i++)
        {
                err = load_mod( cm, mod_path[i] );
                if( err == 0 )
                {
                        HIERR("cosmos_init: warning: load_mod() fail (");
                        HIERR(mod_path[i]);
                        HIERR(")");
                }
        }



        /* make root cosm aframe */

        file_svc_id = cosmos_lookup( mod[0] );

        path_id = cosmos_path_put( cosm_path );

        pi = prod_instr_new();
        pi->fnptr = NULL;
        pi->fnid = file_svc_id;
        pi->argc = 1;
        pi->argv = path_id;

        dc = dcel_new();
        dc->prod_instr = pi;

        af = aframe_new();
        af->cosmos = cm;
        af->dcel = dc;

        af_id = cosmos_aframe_put( cm, af );



        /* parse root cosm */

        xf_id = cosmos_lookup( cm,mod[3] );

        root_cosm_id = cosmos_xformr( cm, xf_id, 1, af_id );

        root_cosm_link_id = cosmos_path_put( cm, "/.cosm" );



        /* link root cosm */

        cosmos_ln( cm, root_cosm_link_id, root_cosm_id );


        return cm;
}
