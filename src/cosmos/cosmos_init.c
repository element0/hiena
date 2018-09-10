#include <libgen.h>    // basename()
#include <unistd.h>    // chdir()
#include <sys/stat.h>
#include <stdint.h>
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
#include "cosmos_config.h"
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
        

        userstr = getlogin();
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





static struct access_frame *init_lookupfn_hdl(struct cosmos *cm)
{
    cosmos_id_t lfh;

    if(cm == NULL)
    {
        HIERR("init_lookupfn_hdl: err cm NULL");
        return NULL;
    }

    if(cm->lookup_dl == NULL)
    {
        HIERR("init_lookupfn_hdl: err cm->lookup_dl NULL");
        return NULL;
    }

    if(cm->proto == NULL)
    {
        HIERR("init_lookupfn_hdl: err cm->proto NULL");
        return NULL;
    }

    lfh = cm->proto->lookfn_hdl = aframe_new();


    /// WIP

    src = prodinstr_new();

    
    prodinstr_append(src,0,dlsym);
    prodinstr_append(src,0,cm->lookup_dl);
    prodinstr_append(src, strlen(CM_LOOKUP_FN_NAME), CM_LOOKUP_FN_NAME);
    prodinstr_set_return_size(src, sizeof(uintptr_t));

    dc = dcel_new();
    dcel_set_prodinstr(dc, src);

    aframe_set_dcel(lfh, dc);
    aframe_set_exec_helper(lfh, 


    return cm->lookfn_hdl;
}



static struct cosmos *cosmos_get_db() {
        return NULL;
}






struct cosmos *cosmos_create_db(int modc, char *mod_path[])
{

        struct cosmos *cm;
        cosmos_id_t proto;
        cosmos_id_t root;
        cosmos_id_t uhost;
        cosmos_id_t userhost;


        ^^^^ wip

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




        /* cosmos proto aframe */
        /* provides inheritance
           for root aframe */


        cm->proto = aframe_new();

        if( cm->proto == NULL )
        {
                HIERR("cosmos_init: err: can't create cosmos proto aframe");

                cosmos_db_cleanup(cm);

                return NULL;
        }



        /* proto lookup fn */
        /* (for lookup in root) */


        printf("lookupmodpath: %s\n", cm->lookupmodpath);
        cm->lookup_dl = dlopen(cm->lookupmodpath,RTLD_NOW);
        if(cm->lookup_dl == NULL)
                printf("%s\n",dlerror());

if(cm->lookup_dl != NULL)
        {
                printf("cm->lookup_dl OPEN\n");

                init_lookupfn_hdl(cm);

        }else{
                printf("cm->lookup_dl == NULL\n");
        }




        /* init mapper function */

        char *mapfnpath = CM_MODLIBPATH "/" CM_SOURCE_MODULE_NAME CM_MODSUFFIX "/" CM_MAP_FN_NAME;


        mode = S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;


        cosmos_mknod_path(cm, cm->proto, mapfnpath, mode, 0 );





        /* ELIMINATE? */
        /* dcel collector */


        cm->dcel = dcel_new(NULL);

        if(cm->dcel == NULL)
        {
                HIERR("cosmos_init: err: cm->dcel NULL");
                cosmos_db_cleanup(cm);
                return NULL;
        }







        /* ELIMINATE? */
        /* cosmos openfiles aframe */

        cm->openfiles = aframe_new();

        if( cm->openfiles == NULL )
        {
                HIERR("cosmos_init: err: can't create cosmos openfiles aframe");

                cosmos_db_cleanup(cm);

                return NULL;
        }




        /* ELIMINATE? */
        /* init modules */
/*

        if( cosmos_init_modules(cm, modc, mod_path) == -1 )
        {
                HIERR("cosmos_init: err: can't init modules");

                cosmos_db_cleanup(cm);

                return NULL;
        }

*/




        /* WIP */


        /* cosmos root aframe */



        cm->root = aframe_spawn(cm->proto); 

        cmroot = cm->root;


        if( cmroot == NULL )
        {
                HIERR("cosmos_init: err: can't create cosmos root");

                cosmos_db_cleanup(cm);

                return NULL;
        }


        mode = S_IFDIR | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;

        rootcosm = cosmos_mkdir( cm, cmroot, ".cosm", mode);

        protocosm = cosmos_lookup( cm, cm->proto, ".cosm" );

        cosmos_cascade_bind( cm, rootcosm, protocosm );


        


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


