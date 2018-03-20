

#include "../cosmos_db.h"
#include "../cosmos_fs.h"
#include "../access_frame.h"
#include "../prod_instr.h"

/** bind external address to target
 *
 */


struct access_frame *cosmos_bind(
    struct cosmos *cm,
    struct access_frame *targ, 
    struct access_frame *modroot,
    char *modpath,
    char *addr )
{

        struct prod_instr *pi;
        struct access_frame *mod;
        struct access_frame *func;
        struct access_frame *par;



        /* create prod instr */

        mod = cosmos_lookup(cm, modroot, modpath);

        func = cosmos_lookup(cm, mod, "cosmos_source_fn");

        par = targ->parent;

        pi = prod_instr_new();
        if(pi == NULL)
        {
                HIERR("cosmos_bind: err: can't alloc prod_instr");
                return NULL;
        }
        pi->module = mod;
        pi->fn = func;
        pi->aframe = par;



        /* create empty dcel */
        /* set prod instr in dcel */


        dc = cosmos_new_dcel( cm );
        dc->prod_instr = pi;




        /* bind dcel to targ */

        targ->dcel = dc;
        dcel_retain(dc);



        return targ;
}