#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <dlfcn.h>
#include "cosmos_db.h"
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






/** load any type of module for 
   cosmos from a pathname;
   store module in a dcel.

   module is accessed by pathname
   or hash id.  pathname is hashed
   to id.  id retrieves module. 

   @param cm   the cosmos db -- do we need this?  TBD
   @param par  the access frame to save the module in
   @param fpath  the module file relative to PWD of process
  */


cosmos_id_t load_mod( struct cosmos *cm, cosmos_id_t par, char *fpath )
{
        if( cm == NULL
         || fpath == NULL )
        {
                HIERR("cosmos_init::load_svc: err: input cm or fpath NULL");

                return NULL;
        }

        void *dl;
        char *dlerr;
        char *svc_name;
        int snlen;
        bkey_t svcid;
        char *fpathdup;
        char *chopoff;
        btree_t *aframes;
        struct access_frame *af;
        struct hiena_dcel *dc;
        cosmos_id_t id;


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



        dl = dlopen(fpath, RTLD_LAZY);
        dlerr = NULL;



        /* note
           may cause valgrind err;
           comment out if need be */

        dlerr = dlerror();

        if(dl == NULL)
        {
                HIERR("mod_load::load_svc: err: dl NULL");
                HIERR(dlerr);
                return NULL;
        }


        /* make dcel */

        dc = dcel_new(NULL);


        /* dcel prod instr

          note
          normally we create a dcel
          by running a prod instr
          which runs a module,
          but this is an init func
          so there might be no mods.
        */

        dc->prod_instr = NULL;



        /* encapsulate dl in dcel
           (sets buffer in mfrag) */

        dcel_set_val(dc, dl, 0);



        /* make access frame */

        af = aframe_new();
        af->dcel = dc;



        /* associate aframe
           with fpath */

        id = cosmos_path_put(cm, fpath);

        return af;
}
