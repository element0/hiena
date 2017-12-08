#include <libgen.h>

char *shortname( char *fpath )
{
        /* strip .suffix */

        char *fpathdup = strndup(fpath, strlen(fpath));

        char *svc_name_tmp = basename(fpathdup);

        char *chopoff = strstr(svc_name_tmp, ".");

        chopoff[0] = '\0';

        char *svc_name = strndup( svc_name_tmp );

        free(fpathdup);

        return svc_name;
}






/** load any type of module for 
   cosmos from a pathname;
   store in cosmos object db.

   module is accessed by pathname
   or hash id.  pathname is hashed
   to id.  id retrieves module. 
  */


cosmos_id_t load_mod( struct cosmos *cm, char *fpath )
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
        cosmos_id_t id;


        /* make sure the fpath 
           contains a slash or
           it may not work like
           I expect. */


        if(strstr(fpath,"/") == NULL)
        {
                HIERR("mod_load: err: fpath must include a '/'";
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



        /* make dcel prod instr

          note
          normally we create a dcel
          by running a prod instr
          which runs a module,
          but this is an init func
          so there might be no mods.

          however, we make a prod
          instr as part of the dcel.
        */

        pi = prod_instr_new();
        pi->fnptr = NULL;
        pi->fnid = dylib_svc_pathid;
        pi->argc = 1;
        pi->argv = fpath_id;


        /* make dcel */

        dc = dcel_new()
        dc->prod_instr = pi;



        /* encapsulate dl in dcel */

        /* sets buffer in mfrag */
        dcel_set_val(dc, dl, 0);



        /* make access frame */

        af = aframe_new();
        af->dcel = dc;



        /* add dl's dcel to db */

        id = hash_sdbm(fpath);
        btree_put(strs, id, fpath);
        btree_put(db, id, dl);

        return id;
}