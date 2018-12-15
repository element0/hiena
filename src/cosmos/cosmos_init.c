#include <libgen.h>    // basename()
#include <unistd.h>    // chdir()
#include <sys/stat.h>
#include <stdint.h>
#include <dlfcn.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "../hierr.h"
#include "../modules/file/file_builtin.h"
#include "../modules/lookup/light/lookup_builtin.h"
#include "../access_frame.h"
#include "../aframe_path.h"
#include "cosmos_db.h"
#include "cosmos_config.h"
#include "cosmos_bind.h"
#include "cosmos_load_module.h"

#include "cosmos_fs.h"
#include "cosmos_xformr.h"

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


static char *user_at_host_str()
{
        char *userstr, *hoststr, *res;
        size_t userstrlen, hoststrlen, reslen, ressize;


        /* fixme - getlogin() not secure
           do not free 'userstr' */
        userstr = getlogin();

        hoststr = malloc(sizeof(char)*HOST_NAME_MAX);
        memset(hoststr, 0, sizeof(char)*HOST_NAME_MAX);
        gethostname(hoststr, HOST_NAME_MAX);

        userstrlen = strlen(userstr);
        hoststrlen = strlen(hoststr);

        reslen = userstrlen+1+hoststrlen+1;
        ressize = sizeof(char)*reslen;
        res = malloc(ressize);

        
        snprintf(res, ressize, "%s@%s", userstr, hoststr);

        
        free(hoststr);

        return res;
}








static struct cosmos *cosmos_get_db() {
        return NULL;
}







struct cosmos *cosmos_create_db(int modc, char *mod_path[])
{

        struct cosmos *cm;
        cosmos_id_t root;
        cosmos_id_t userhostroot;
        cosmos_id_t mod;
        cosmos_module_t *lookmod;
        cosmos_module_t *svcmod;

        mode_t mode;
        size_t len;
        char *buf, *userhoststr;



  /*******************************/

        /*
         * cosmos db
         */


        cm = cosmos_db_new();

        if(cm == NULL)
        {
                HIERR("cosmos_create_db: err: fail to allocate cosmos db");
                return NULL;
        }



  /*******************************/

        /*
         * config
         */


        if(cosmos_config(cm) == -1)
        {
HIERR("cosmos_create_db: err: fail to configure cosmos db");
                return NULL;
        }




  /*******************************/

        /*
         * cosmos db root
         */


        cm->root = aframe_new();

        if( cm->root == NULL )
        {
                HIERR("cosmos_init: err: can't create cosmos root");

                cosmos_db_cleanup(cm);

                return NULL;
        }

  /*******************************/

        /*
         * user@host root
         */

        userhoststr = user_at_host_str();

        userhostroot = aframe_set_branch(cm->root, cosmos_put_string(cm,userhoststr), aframe_new());

        free(userhoststr);

        if(cosmos_bind(cm, userhostroot, cm->root_src_url, NULL) != userhostroot)
        {
                HIERR("cosmos_init: err: can't bind userhostroot to root_src_url");

                        cosmos_db_cleanup(cm);

                return NULL;

        }


        aframe_set_parent(userhostroot, userhostroot);


  /*******************************/


        /*
         * load lookup module
         */

        lookmod = &cosmos_lookup_builtin;



        /*
         * save in db
         *

using the module:

cosmos_lookup will invoke the lookup module directly.  it looks for the module handle relative to the parent's metadir:

         example/../.cosm/lib/cosmos/modules/lookup.so

         
        *
        */


        /* make access path
           using aframe branches
         */

        len = sizeof(char)*(
strnlen(cm->metadirname, PATH_MAX)+
strnlen(cm->modrelpath, PATH_MAX)+
strnlen(cm->lookupmodname, PATH_MAX)+ 1);

        buf = malloc(len);

        snprintf(buf, len, "%s/%s/%s", cm->metadirname, cm->modrelpath, cm->lookupmodname );

        mod = aframe_mkflatpath(cm, userhostroot, buf);

        aframe_set_value_ptr(mod, lookmod);

        free(buf);


  /*******************************/


        /*
         * load service module
         */

        svcmod = &cosmos_file_builtin;


        /*
         * save in db
         *

using the module:

dcel ops will invoke the module indirectly:  stat, opendir, open, etc.

inside the dcel op, we look for the module handle relative to the parent's metadir:

         example/../.cosm/lib/cosmos/modules/$module
         
        *
        */


        /* make path
           using aframe branch cache
         */


        len = sizeof(char)*(
strnlen(cm->metadirname, PATH_MAX)+
strnlen(cm->modrelpath, PATH_MAX)+
strnlen(cm->svcmodname, PATH_MAX)+ 1);
        buf = malloc(len);
        snprintf(buf, len, "%s/%s/%s", cm->metadirname, cm->modrelpath, cm->svcmodname );

        mod = aframe_mkflatpath(cm, root, buf);

        aframe_set_value_ptr(mod, svcmod);


        free(buf);


  /*******************************/




        return cm;
}







struct cosmos *cosmos_init(int modc, char *mod_path[])
{

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


