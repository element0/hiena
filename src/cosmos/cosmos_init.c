
#include <libgen.h>    // basename()
#include "../hierr.h"
#include "../prod_instr.h"
#include "../dcel.h"
#include "../access_frame.h"
#include "cosmos_db.h"
#include "cosmos_fs.h"
#include "cosmos_xformr.h"
#include "load_module.h"


/* EXAMPLE:
static void example_init_seq()
{
        struct cosmos *cm;
        int modc = 6;
        char *mod_path[] = {
  "/usr/lib/cosmos",
  "/usr/lib/cosmos/svc/file.so",
  "/usr/lib/cosmos/xformr/dcelcosm.so",
  "/usr/lib/cosmos/lookup/fudge.so",
  "/usr/lib/cosmos/svc/dylib.so",
  "/usr/lib/cosmos/svc/ptr.so",

        };

        cm = cosmos_init(modc, mod_path);

}
*/


struct cosmos *cosmos_init(int modc, char *mod_path[])
{
        if( modc < 3
          || mod_path = NULL )
        {
                HIERR("cosmos_init: err: modc < 3 || mod_path NULL");
                return NULL;
        }


        struct cosmos *cm;
        int i;
        cosmos_id_t err;
        cosmos_id_t base_svc_id;
        cosmos_id_t cosm_src_id;
        cosmos_id_t af_id;
        cosmos_id_t xf_id;
        cosmos_id_t root_cosm_id;
        cosmos_id_t root_cosm_link_id;
        struct prod_instr *pi;
        struct hiena_dcel *dc;
        struct access_frame *af;

        cm = cosmos_db_new();



        /* parse args 1 and 2 */


        cosm_src_id = cosmos_path_put( cm, mod_path[0] );

        base_svc_id = load_mod( cm, mod_path[1] );

        xf_id = load_mod(cm, mod_path[2] );



        /* load addtl modules */


        for(i=2; i<modc; i++)
        {
                err = load_mod( cm, mod_path[i] );
                if( err == 0 )
                {
                        HIERR("cosmos_init: warning: load_mod() fail (");
                        HIERR(mod_path[i]);
                        HIERR(")");
                }
        }



        /* setup root cosm src */

  /*----> wip  */

        pi = prod_instr_new();
        pi->fnid = (prodfn_guid_t)base_svc_id;

        // argc 0 means argv is valu
        pi->argc = 0;
        pi->argv = (void **)cosm_src_id;


        dc = dcel_new(NULL);
        dc->prod_instr = pi;

        af = aframe_new();
        af->cosmos = cm;
        af->dcel = dc;

        af_id = cosmos_aframe_put( cm, "/.cosm", af );



        /* parse root cosm */

        root_cosm_id = cosmos_xformr(cm, xf_id, 1, (void **)af_id);





        /* link root cosm */

        root_cosm_link_id = cosmos_path_put( cm, "/.cosm" );

        cosmos_ln( cm, root_cosm_link_id, root_cosm_id );


        return cm;
}
