#include <string.h>
#include "cosmos_db.h"
#include "cosmos_config.h"
#include "../hierr.h"

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



        cm->modlibpath = CM_MODLIBPATH;

        cm->modlibpathlen = strlen(cm->modlibpath);

        cm->modsuffix = CM_MODSUFFIX;

        cm->modsuffixlen = strlen(cm->modsuffix);


        cm->modsymbols = cm_mod_symbols;



        homedir = getenv("HOME");

        modpath_half = "/" CM_MODLIBPATH "/" CM_LOOKUP_MODULE_NAME CM_MODSUFFIX;
        
        modpath = malloc(sizeof(char)*(strlen(homedir)+strlen(modpath_half)+1));

        modpath[0] = '\0';

        strncat(modpath, homedir, strlen(homedir));

        strncat(modpath, modpath_half, strlen(modpath_half));




        cm->lookupmodpath = modpath;




        return 0;

}
