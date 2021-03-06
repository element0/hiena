#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <dlfcn.h>
#include "cosmos_db.h"
#include "cosmos_dlfcn.h"
#include "cosmos_module.h"
#include "../dcel.h"
#include "../access_frame.h"
#include "../hierr.h"






char *shortname( char *fpath )
{
        /* strip .suffix */

        char *fpathdup = strndup(fpath, strlen(fpath));

        char *svc_name_tmp = basename(fpathdup);

        char *chopoff = strstr(svc_name_tmp, ".");

        chopoff[0] = '\0';

        char *svc_name = strndup(svc_name_tmp, strlen(svc_name_tmp));

        free(fpathdup);

        return svc_name;
}




cosmos_module_t *cosmos_load_mod( struct cosmos *cm, char *fpath )
{
        if( cm == NULL
         || fpath == NULL )
        {
                HIERR("cosmos_init::load_svc: err: input cm or fpath NULL");
 
                return NULL;
        }

        cosmos_module_t *mod;
        void *dl = NULL;
        char *dlerr = NULL;
        int err = 0;



        /* make sure the fpath 
           contains a slash or
           it may not work like
           you expect. */


        if(strstr(fpath,"/") == NULL)
        {
                HIERR("mod_load: err: fpath must include a '/'");
                return NULL;
        }



        /* load dylib */

        dl = dlopen(fpath, RTLD_LAZY);

        dlerr = NULL;



        /* note
           dlerror()
           may cause valgrind err;
           not included here. */



        if(dl == NULL)
        {
                HIERR("cosmos_load_mod::load_svc: err: dl NULL");
                // HIERR(dlerr);
                return NULL;
        }


        mod = cosmos_module_new();

        // save the dl in the module

        mod->dl = dl;


        // link whatever succeeds

        (mod->svc = dlsym(dl, "svc")) ? 1 : err++;

        (mod->map = dlsym(dl, "map"))? 1 : err++;

        (mod->lookup = dlsym(dl, "lookup")? 1 : err++;

        (mod->grind = dlsym(dl, "grind")? 1 : err++;


        if( err == 4 )
        {
                HIERR("cosmos_load_mod: err: no module services found");
                HIERR(fpath);
                cosmos_module_cleanup(mod);
                return NULL;
        }

        mod = cosmos_module_new();

        // save the dl in the module

        mod->dl = dl;


        // link whatever succeeds

        (mod->svc = dlsym(dl, "svc")


        return mod;
}


struct cosmos_module *cosmos_load_mod_builtin( struct cosmos *cm, char *modname )
{
        struct cosmos_module *mod;


        if( cm == NULL
         || modname == NULL )
        {
                HIERR("cosmos_load_mod_builtin::load_svc: err: input cm or modname NULL");
 
                return NULL;
        }

        mod = cosmos_module_new();

        // save the dl in the module

        mod->dl = NULL;


        // link whatever succeeds

        mod->svc = dlsym(NULL, modname)

        return mod;
}


struct cosmos_module *cosmos_load_mod_vfn( struct cosmos *cm, char *fpath )
        if( cm == NULL
         || fpath == NULL )
        {
                HIERR("cosmos_init::load_svc: err: input cm or fpath NULL");
 
                return NULL;
        }

        cosmos_module_t *mod;
        void *dl = NULL;
        char *dlerr = NULL;
        int err = 0;



        /* make sure the fpath 
           contains a slash or
           it may not work like
           I expect. */


        if(strstr(fpath,"/") == NULL)
        {
                HIERR("mod_load: err: fpath must include a '/'");
                return NULL;
        }



        /* load dylib */
        /* use cosmos_dlopen for transparent RPC. */


        dl = dlopen(fpath, RTLD_LAZY);

        dlerr = NULL;



        /* note
           dlerror()
           may cause valgrind err;
           not included here. */



        if(dl == NULL)
        {
                HIERR("mod_load::load_svc: err: dl NULL");
                // HIERR(dlerr);
                return NULL;
        }


        mod = cosmos_module_new();

        // save the dl in the module

        mod->dl = dl;

        // link whatever succeeds

        (mod->svc = cosmos_dlsym(dl, "struct hiena_service *svc")) ? 1 : err++;

        (mod->map = cosmos_dlsym(dl, "int map(Hsp *hsp)"))? 1 : err++;

        (mod->lookup = cosmos_dlsym(dl, "cosmos_id_t lookup(struct cosmos *cm, cosmos_id_t par, char *rqstr)")?1:err++;

        (mod->grind = cosmos_dlsym(dl, "void *grind(void *, ...)")?1:err++;


        if( err == 4 )
        {
                HIERR("cosmos_load_mod: err: no module services found");
                HIERR(fpath);
                cosmos_module_cleanup(mod);
                return NULL;
        }


        return mod;
}
