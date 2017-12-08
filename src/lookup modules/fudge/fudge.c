
#include "../../lookup_hdl.h"
#include "../../dcel.h"
#include "fudge.h"

struct hiena_dcel *fudge_seg( struct hiena_dcel *dc, char *s )
{
        if( dc == NULL
         || s == NULL )
        {
                return NULL;
        }
        
}

struct hiena_dcel *fudge( struct hiena_dcel *, char *, char * )
{
        if( dc == NULL
         || s == NULL )
        {
                return NULL;
        }
}

char *fudge_expand(struct lookup_hdl *look, char *s)
{
        struct cosmos_cosm *cosm;
        struct hiena_dcel *cmdob;
        char *cmd;
        
        cosm = look->cosm;
        cmdob = fudge(cosm, "conf/fudge:alias/%s", s);
        cmd = dcel_strcpy(cmdob);
        
        return cmd;
}