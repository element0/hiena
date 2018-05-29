#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cosmos_db.h"
#include "../hierr.h"


char *cosmos_calc_fnpath(struct cosmos *cm, char *modname, char *fnname)
{
        char *fnpath, *cur;
        size_t len;
        char *modlibpath, *modsuffix;
        size_t fnpathsize, modlibpathlen, modnamelen, modsuffixlen, fnnamelen;

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
        modsuffix = cm->modsuffix;

        modlibpathlen = cm->modlibpathlen;
        modsuffixlen = cm->modsuffixlen;
        modnamelen = strlen(modname);
        fnnamelen = strlen(fnname);


        fnpathsize = sizeof(char)*
(modlibpathlen+1
+modnamelen
+modsuffixlen+1
+fnnamelen+1);


        fnpath = malloc(fnpathsize);

        cur = fnpath;

        strncpy(cur, modlibpath, modlibpathlen);
        cur += modlibpathlen;

        (cur++)[0] = '/';

        strncpy(cur, modname, modnamelen);
        cur += modnamelen;

        strncpy(cur, modsuffix, modsuffixlen);
        cur += modsuffixlen;

        (cur++)[0] = '/';

        strncpy(cur, fnname, fnnamelen);
        cur += fnnamelen;

        cur[0] = '\0';

        return fnpath;
}