#include <libgen.h>    // basename()
#include <unistd.h>    // chdir()
#include <sys/stat.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
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
        int modc = 3;
        char *mod_path[] = {
            "/usr/lib/cosmos",
            "lookup/fudge.so",
            "svc/file.so",
        };

        cm = cosmos_init(modc, mod_path);

}
*/


static char *user_at_host_string()
{
        char *userstr, *hoststr, *res;
        size_t userstrlen, hoststrlen, reslen, ressize;
        

        userstr = "d";
        hoststr = "mohost.local";

        userstrlen = strlen(userstr);
        hoststrlen = strlen(hoststr);

        reslen = userstrlen+1+hoststrlen+1;
        ressize = sizeof(char)*reslen;
        res = malloc(ressize);

        
        res = strncat(res,userstr,userstrlen);
        res = strncat(res,"@",1);
        res = strncat(res,hoststr,hoststrlen);
        res[reslen-1] = '\0';
        

        return res;
}
















static struct cosmos *cosmos_get_db() {
        return NULL;
}







struct cosmos *cosmos_create_db(int modc, char *mod_path[])
{

        struct cosmos *cm;
        cosmos_id_t boot_cosm;
        cosmos_id_t uhost_nod;
        cosmos_id_t cmroot;
        cosmos_id_t hostcosm;
        cosmos_id_t userhost;
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



        cm->root = aframe_new(); 

        cmroot = cm->root;

        if( cmroot == NULL )
        {
                HIERR("cosmos_init: err: can't get cosmos root");

                cosmos_db_cleanup(cm);

                return NULL;
        }

        cmroot->parent = cm->proto;





        /* init modules */



/*

        if( cosmos_init_modules(cm, modc, mod_path) == -1 )
        {
                HIERR("cosmos_init: err: can't init modules");

                cosmos_db_cleanup(cm);

                return NULL;
        }

*/
        


        /* init host cosm */


/*

        mode = S_IFDIR | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;



        hostcosm = cosmos_mkdir( cm, cmroot, ".cosm", mode);

        if(hostcosm == NULL)
        {
                HIERR("cosmos_create_db: err: can't init hostcosm");

                cosmos_db_cleanup(cm);

                return NULL;
        }



        cosmos_bind(cm, hostcosm, "file", mod_path[0], cmroot);

*/


        /* init user-host cosm */

/*

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


*/

        return cm;
}







struct cosmos *cosmos_init(int modc, char *mod_path[])
{
/*
        if( modc < 3
          || mod_path == NULL )
        {
                HIERR("cosmos_init: err: modc < 3 || mod_path NULL");
                return NULL;
        }
*/


        struct cosmos *cm;




        cm = cosmos_get_db();

        if( cm != NULL )
                return cm;



        cm = cosmos_create_db(modc, mod_path);


        if( cm == NULL )
        {
                HIERR("cosmos_init: err: can't create cosmos db");

                return NULL;
        }


        return cm;
}


