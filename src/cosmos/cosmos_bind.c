

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
        struct hiena_dcel *dc;


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



        dc = cosmos_new_dcel( cm );

        dc->module = cosmos_string_id( protocol );
        dc->addr = cosmos_put_string( cm, addr );

        dcel_release( dest->dcel );

        dest->dcel = dc;
        dcel_retain( dc );



        return dest;

abort:
        return COSMOS_ID_NULL;

}