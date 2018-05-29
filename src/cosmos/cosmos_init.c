#include <libgen.h>    // basename()
#include <unistd.h>    // chdir()
#include <sys/stat.h>
#include <dlfcn.h>
#include "../hierr.h"
#include "../prod_instr.h"
#include "../dcel.h"
#include "../access_frame.h"
#include "cosmos_db.h"
#include "cosmos_fs.h"
#include "cosmos_xformr.h"
#include "load_module.h"
#include <errno.h>


/* EXAMPLE:
static void example_init_seq()
{
        struct cosmos *cm;
        int modc = 3;
        char *mod_path[] = {
            "/usr/lib/cosmos",
            "lookup/fudge.so",
            "svc/file.so",
        };

        cm = cosmos_init(modc, mod_path);

}
*/


static int cosmos_init_modules(struct cosmos *cm, int modc, char *mod_path[]) {

        /* call from cosmos_init.
           cosmos_init has checked
           the args */

        struct access_frame *af;

        char *buf[PATH_MAX];
        char *dsav;


        dsav = getcwd(&buf, PATH_MAX);

        if( dsav == NULL )
        {
                if( errno == ERANGE )
                        HIERR("cosmos_init_modules: err: getcwd ERANGE");
                else
                        HIERR("cosmos_init_modules: err: getcwd NULL");
                
                return -1;
        }


        chdir(mod_path[0]);


        af = cm->aframe;


        cosmos_ll_mknod_path(cm, af, "init/lookup");



        if(( lookmod = cosmos_loadmod(cm, "init/lookup", mod_path[2])) == -1)
        {
                HIERR("cosmos_init_modules: err: lookup not loaded");

                return -1;
        }

        
        af = cm->proto;
        if(af == NULL)
        {
                HIERR("cosmos_init_modules: err: cm->proto NULL");

                return -1;
        }


        if((af->lookfn = dlsym((void *)aframe_val_ptr(lookmod), "cosmos_lookup_fn")) == NULL )
        {
                HIERR("cosmos_init_modules: err: proto->lookfn NULL");

                return -1;
        }



        af = cm->aframe;

        cosmos_ll_mknod_path(cm, af, "init/filesvc");


        if( cosmos_loadmod(cm, "init/filesvc", mod_path[1]) == -1)
        {
                HIERR("cosmos_init_modules: err: filesvc not loaded");

                return -1;
        }


        chdir( dsav );

        return 0;
}













static struct cosmos *cosmos_get_db() {
        return NULL;
}







struct cosmos *cosmos_create_db(int modc, char *mod_path[]) {

        struct cosmos *cm;
        cosmos_id_t *boot_cosm;
        cosmos_id_t *uhost_nod;
        mode_t mode;
        char *userhost_str;




        cm = cosmos_db_new();

        if(cm == NULL)
        {
                HIERR("cosmos_create_db: err: fail to allocate cosmos db");
                return NULL;
        }



        /* config */

        if(cosmos_config(cm) == -1)
        {
HIERR("cosmos_create_db: err: fail to configure cosmos db");
                return NULL;
        }



        cm->dcel = dcel_new(NULL);

        if(cm->dcel == NULL)
        {
                HIERR("cosmos_init: err: cm->dcel NULL");
                cosmos_db_cleanup(cm);
                return NULL;
        }



        


        /* cosmos proto aframe */



        cm->proto = aframe_new();

        if( cm->proto == NULL )
        {
                HIERR("cosmos_init: err: can't get cosmos proto aframe");

                cosmos_db_cleanup(cm);

                return NULL;
        }





        /* cosmos root aframe */



        cm->aframe = aframe_new(); 

        cmroot = cm->aframe;

        if( cmroot == NULL )
        {
                HIERR("cosmos_init: err: can't get cosmos root");

                cosmos_db_cleanup(cm);

                return NULL;
        }

        cmroot->parent = cm->proto;





        /* init modules */





        if( cosmos_init_modules(cm, modc, mod_path) == -1 )
        {
                HIERR("cosmos_init: err: can't init modules");

                cosmos_db_cleanup(cm);

                return NULL;
        }


        


        /* init host cosm */


        mode = S_IFDIR | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;



        hostcosm = cosmos_mkdir( cm, cmroot, ".cosm", mode);

        if(hostcosm == NULL)
        {
                HIERR("cosmos_create_db: err: can't init hostcosm");

                cosmos_db_cleanup(cm);

                return NULL;
        }



        cosmos_bind(cm, hostcosm, cmroot, "init/filesvc", mod_path[0]);

        



        /* init user-host cosm */

        userhost_str = user_at_host_string();

        if( userhost_str == NULL )
        {
                HIERR("cosmos_create_db: err: can't create userhost_str");

                cosmos_db_cleanup(cm);

                return NULL;
        }


        userhost = cosmos_mkdir( cm, cmroot, userhost_str, mode);

        if(hostcosm == NULL)
        {
                HIERR("cosmos_create_db: err: can't init userhost");

                free(userhost_str);
                cosmos_db_cleanup(cm);

                return NULL;
        }

        free(userhost_str);



        cosmos_bind(cm, userhost, cmroot, "init/filesvc", "/");




        return cm;
}







struct cosmos *cosmos_init(int modc, char *mod_path[])
{
        if( modc < 3
          || mod_path == NULL )
        {
                HIERR("cosmos_init: err: modc < 3 || mod_path NULL");
                return NULL;
        }



        struct cosmos *cm;




        cm = cosmos_get_db();

        if( cm != NULL )
                return cm;



        cm = cosmos_create_db();


        if( cm == NULL )
        {
                HIERR("cosmos_init: err: can't create cosmos db");

                return NULL;
        }


        return cm;
}


