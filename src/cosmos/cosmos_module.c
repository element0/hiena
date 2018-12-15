#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cosmos_db.h"
#include "../hierr.h"


char *cosmos_calc_fnpath(struct cosmos *cm, char *modname, char *fnname)
{
        char *fnpath, *cur;
        size_t len;
        char *moddirpath, *modsuffix;
        size_t fnpathsize, moddirpathlen, modnamelen, modsuffixlen, fnnamelen;

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


        moddirpath = cm->moddirpath;
        modsuffix = cm->modsuffix;

        moddirpathlen = cm->moddirpathlen;
        modsuffixlen = cm->modsuffixlen;
        modnamelen = strlen(modname);
        fnnamelen = strlen(fnname);


        fnpathsize = sizeof(char)*
(moddirpathlen+1
+modnamelen
+modsuffixlen+1
+fnnamelen+1);


        fnpath = malloc(fnpathsize);

        cur = fnpath;

        strncpy(cur, moddirpath, moddirpathlen);
        cur += moddirpathlen;

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