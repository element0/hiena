#include <string.h>
#include "cosmos_db.h"
#include "cosmos_config.h"
#include "../hierr.h"


char *cm_mod_symbols[]={
    "open",
    "close",
};



int cosmos_config(struct cosmos *cm)
{
        char *homedir;
        char *modpath;
        char *modpath_half;


        if( cm == NULL )
        {
                HIERR("cosmos_config: cm NULL");
                return -1;
        }


/**********************************/

 /* metadirectory relative paths */

        cm->metadirname = COSMOS_METADIR_NAME;

        cm->host_lookupmod_fpath = COSMOS_HOST_LOOKUPMOD_FPATH;

        cm->host_svcmod_fpath = COSMOS_HOST_SVCMOD_FPATH;



/* OS relative suffixes */

        cm->modsuffix = COSMOS_MOD_SUFFIX;


/**********************************/

        /* install paths */



/**********************************/


        cm->modsymbols = cm_mod_symbols;

        cm->moddirpath = COSMOS_HOST_MODDIR_PATH;


/**********************************/

/* precalculated string lengths */

        cm->moddirpathlen = strlen(cm->moddirpath);

        cm->modsuffixlen = strlen(cm->modsuffix);




/**********************************/



        cm->lookup_dl = NULL;

/*
        homedir = getenv("HOME");

        modpath_half = "/" CM_MODLIBPATH "/" CM_LOOKUP_MODULE_NAME CM_MODSUFFIX;
        
        modpath = malloc(sizeof(char)*(strlen(homedir)+strlen(modpath_half)+1));

        modpath[0] = '\0';

        strncat(modpath, homedir, strlen(homedir));

        strncat(modpath, modpath_half, strlen(modpath_half));


*/


        return 0;

}
