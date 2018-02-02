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
            "lookup/fudge.so",
            "svc/file.so",
            "xformr/dcelcosm.so",
            "svc/dylib.so",
            "svc/ptr.so",
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
        cosmos_id_t boot_cosm;
        cosmos_id_t *uhost_nod;

        int i;
        char *cosm_src_path;
        struct cosmos *cm;
        struct access_frame *db_root_af;

        struct access_frame *tmp;
        struct access_frame *cur;
        struct access_frame *mod;
        struct prod_instr *pi;
        struct hiena_dcel *dc;
        struct access_frame *af;
        void *dl, *fn;







        /* init db object */

        cm = cosmos_db_new();

        if(cm == NULL)
        {
                HIERR("cosmos_init: err: fail to allocation cosmos db");
                return NULL;
        }

        cm->aframe = aframe_new(); 

        if(cm->aframe == NULL)
        {
                HIERR("cosmos_init: err: cm->aframe NULL");
                cosmos_db_cleanup(cm);
                return NULL;
        }
        
        cm->dcel = dcel_new(NULL);




        /* default access paths */

        char *ap[]={
                ".cosm",
                "demo@localhost",
        };

        boot_cosm = cosmos_mkdir(cm, (cosmos_id_t)(cm->aframe), ap[0], S_IFDIR | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

        uhost_nod = cosmos_mkdir(cm, (cosmos_id_t)(cm->aframe), ap[1], S_IFDIR | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);





        /* initial modules */

        /* .cosm/lookup/fudge.so.dlopen.dlsym/lookup_fn */

        i = 0;
        cosm_src_path = mod_path[i+++];
        chdir(cosm_src_path);

        tmp = cosmos_mknod( cm, boot_cosm, mod_path[i],
S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0 );

        mod = load_mod( cm, boot_cosm, mod_path[i++] );

        cosmos_ln( cm, mod, tmp, "dlopen" );

        /* need to set mode above */

        tmp = cosmos_mkdir( cm, mod, "dlsym",
S_IFDIR | S_IRWXU | S_IRGRP | 0S_IXGRP | S_IROTH | S_IXOTH );

        tmp = cosmos_mknod( cm, tmp, "lookup_fn",
S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0 );




        /* link lookup function */

        dc = mod->dcel;

        dl = dcel_get_val( dc );
        
        if( dl == NULL )
        {
                HIERR("cosmos_init: err: dl, dcel_get_val NULL");
                cosmos_db_cleanup(cm);

                return NULL;
        }

        
        fn = dlsym( dl, "lookup_fn" );

        if( fn == NULL )
        {
                HIERR("cosmos_init: err: fn NULL");
        }

        cm->aframe->lookfn = fn;

        /* todo:  link fn to tmp */



        /* load base svc mod */

        /* .cosm/svc/file.so.dlopen.dlsym/sourcer_fn */

        tmp = cosmos_mknod_path( cm, boot_cosm, mod_path[i], S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0);


        cm->base_svc = tmp;

        mod = load_mod( cm, cur, mod_path[i++] );

        cosmos_ln( cm, mod, tmp, "dlopen" );

        /* need to set mode above */

        tmp = cosmos_mkdir( cm, mod, "dlsym",
S_IFDIR | S_IRWXU | S_IRGRP | 0S_IXGRP | S_IROTH | S_IXOTH );

        tmp = cosmos_mknod( cm, tmp, "lookup_fn",
S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0 );



        dc = mod->dcel;
        dl = dcel_get_val( dc );
       
        if( dl == NULL )
        {
                HIERR("cosmos_init: err: loading base svc: dl, dcel_get_val NULL");
                cosmos_db_cleanup(cm);

                return NULL;
        }

        
        fn = dlsym( dl, "sourcer_fn" );

        if( fn == NULL )
        {
                HIERR("cosmos_init: err: sourcer_fn NULL");
        }

        /* todo:  link fn to aframe */


        


        /* init host cosm */

        // create .cosm with dcel with file svc

        pi = prod_instr_new();
        pi->fnptr = fn;

        

        ...

        /* init user-host cosm */

        create userhost aframe
        create .cosm stub
        cascade with parent cosm
        ...





        /* load modules */

        for(i=2; i<modc; i++)
        {
                cur = cosmos_mknod_path( cm, boot_cosm, mod_path[i], S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0);

                mod = load_mod( cm, cur, mod_path[i] );
                if( mod == 0 )
                {
                        HIERR("cosmos_init: warning: load_mod() fail (");
                        HIERR(mod_path[i]);
                        HIERR(")");
                }
        }

        return cm;
}
