
#include "../../lookup_svc.h"
#include "../../cosmos.h"
#include "fudge.h"



cosmos_id_t cosmos_lookup_fn ( struct cosmos *cm, cosmos_id_t par, char *rqstr )
{
        struct lookup_hdl *h;
        cosmos_id_t res;
        int err;

        h = lookup_hdl_new();

        h->cosmos = cm;
        h->aframe = par;
        h->str = rqstr;


        err = fudge_parse( h );

        res = (cosmos_id_t)(h->targ);

        return res;
}



/* fudge_expand() may expand to
       a sequence of modifiers,
       in which case it will call
       look->set_target() for each.
 */

int fudge_expand(yyscan_t scanner, struct lookup_hdl *look, char *s)
{
        struct cosmos_cosm *cosm;
        struct hiena_dcel *cmdob;
        char *str;
        
        /* expand fudge alias */
            /* lookup cosm */
        
        /* parse alias */

        yyparse(scanner, h);

        /* return success */

        cosm = look->cosm;
        cmdob = fudge(cosm, "conf/fudge:alias/%s", s);
        cmd = dcel_strcpy(cmdob);
        
        return cmd;
}
