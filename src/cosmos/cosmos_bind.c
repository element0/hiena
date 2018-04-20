

#include "../cosmos_db.h"
#include "../cosmos_fs.h"
#include "../access_frame.h"
#include "../prod_instr.h"



/** bind a single external address to a cosmos id 
 *
 */

cosmos_id_t cosmos_bind(
    struct cosmos *cm,
    cosmos_id_t dest,
    char *protocol,
    char *addr,
    cosmos_id_t context)

{
        cosmos_id_t par;
        cosmos_id_t cosmdir;
        cosmos_id_t protdir;
        cosmos_id_t protmod;

        /* cosmos meta dir name
           cm->cosmos_dirname */

        /* protocol dir path
           cm->protocol_dirpath */

        struct prod_instr *pi;
        
        /* production function id
           DCEL_SOURCE */


        if( cm == NULL )
        {
                HIERR("cosmos_bind: err: input cm NULL");
                goto abort;
        }

        if( dest == COSMOS_ID_NULL )
        {
                HIERR("cosmos_bind: err: input dest NULL");
                goto abort;
        }

        if( protocol == NULL )
        {
                HIERR("cosmos_bind: err: input protocol NULL");
                goto abort;
        }

        if( addr == NULL )
        {
                HIERR("cosmos_bind: err: input addr NULL");
                goto abort;
        }



        /* get protocol module */

        par = dest->parent;

        cosmdir = cosmos_lookup(cm, par, cm->cosmos_dirname);

        protdir = cosmos_lookup(cm, cosmdir, cm->protocol_dirpath);

        protmod = cosmos_lookup(cm, protdir, protocol);





        /* create prod instr */

        pi = prod_instr_new();

        if(pi == NULL)
        {
                HIERR("cosmos_bind: err: can't alloc prod_instr");
                return NULL;
        }

        pi->module = protmod;
        pi->fnid = DCEL_SOURCE;
        pi->aframe = par;




        /* create dcel
           set prod instr */

        dc = cosmos_new_dcel( cm );
        dc->prod_instr = pi;





        /* remove existing bind */

        dcel_release( targ->dcel );





        /* bind dcel to dest */

        targ->dcel = dc;
        dcel_retain( dc );




        return dest;

abort:
        return COSMOS_ID_NULL;

}