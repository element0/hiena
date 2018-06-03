#include <string.h>
#include "cosmos_db.h"
#include "cosmos_config.h"
#include "../hierr.h"

int cosmos_config(struct cosmos *cm)
{
        if( cm == NULL )
        {
                HIERR("cosmos_config: cm NULL");
                return -1;
        }

        cm->modlibpath = CM_MODLIBPATH;
        cm->modlibpathlen = strlen(cm->modlibpath);
        

        cm->modsuffix = CM_MODSUFFIX;
        cm->modsuffixlen = strlen(cm->modsuffix);
       
        cm->lookupmodpath = "/home/raygan/" CM_MODLIBPATH "/lookup.so";



        return 0;

}
