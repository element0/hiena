#include <stdlib.h>
#include <stdio.h>
#include <string.h>



char *cosmos_calc_fnpath(struct cosmos *cm, char *modname, char *fnname)
{
        char *fnpath;
        int len;
        char *modlibpath;

        if( cm == NULL )
        {
                HIERR("cosmos_calc_fnpath: cm NULL");
                return NULL;
        }


        if( modname == NULL )
        {
                HIERR("cosmos_calc_fnpath: modname NULL");
                return NULL;
        }


        if( fnname == NULL )
        {
                HIERR("cosmos_calc_fnpath: fnname NULL");
                return NULL;
        }


        modlibpath = cm->modlibpath;

        fnpath = malloc(sizeof(char)*
(strlen(modlibpath+1
+strlen(modname)
+strlen(modsuffix)+1
+strlen(fnname)+1)
);


        
}