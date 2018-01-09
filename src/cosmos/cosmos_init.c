#include <libgen.h>     // basename()
#include <unistd.h>     // chdir()
#include <sys/stat.h>
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
          || mod_path == NULL )
        {
                HIERR("cosmos_init: err: modc < 3 || mod_path NULL");
                return NULL;
        }


        cosmos_id_t af_id;
        cosmos_id_t xf_id;
        cosmos_id_t root_cosm_id;
        cosmos_id_t root_cosm_link_id;

        int i;
        char *cosm_src_path;
        struct cosmos *cm;
        struct access_frame *db_root_af;
        struct access_frame *boot_cosm;
        struct access_frame *uhost_cosm;
        struct access_frame *cur_path;
        struct access_frame *mod;
        struct prod_instr *pi;
        struct hiena_dcel *dc;
        struct access_frame *af;


        /* default access paths */

        char *ap[]={
                ".cosm",
                "demo@localhost",
        };



        /* allocate db object */

        cm = cosmos_db_new();
        cm->aframe = aframe_new(); 
        cm->dcel = dcel_new(NULL);


        /* setup "boot" cosm */

        boot_cosm = cosmos_mkdir(cm, cm->aframe, ".cosm", S_IFDIR | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);



        /* setup user-host-context */

        uhost_cosm = cosmos_mknod(cm, cm->aframe, "demo@localhost", S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0);




        /* load modules */

        cosm_src_path = mod_path[0];
        chdir(cosm_src_path);

        for(i=1; i<modc; i++)
        {
                cur_path = cosmos_mknod_path( cm, boot_cosm, mod_path[i], S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0);
                mod = load_mod( cm, cur_path, mod_path[i] );
                if( mod == 0 )
                {
                        HIERR("cosmos_init: warning: load_mod() fail (");
                        HIERR(mod_path[i]);
                        HIERR(")");
                }
        }




        return cm;
}
