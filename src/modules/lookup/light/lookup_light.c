#include "../../../lookup_svc.h"
#include "../../../cosmos.h"
#include "../../../hierr.h"


cosmos_id_t cosmos_lookup_fn ( struct cosmos *cm, cosmos_id_t par, char *rqstr )
{
        struct lookup_hdl *h;
        cosmos_id_t res;
        int err;

        h = lookup_hdl_new();

        h->cosmos = cm;
        h->aframe = par;
        h->str = rqstr;




        res = (cosmos_id_t)(h->targ);

        return res;
}