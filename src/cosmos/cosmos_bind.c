#include <stdlib.h>
#include <string.h>

#include "../cosmos.h"
#include "../access_frame.h"
#include "../prod_instr.h"
#include "../hierr.h"







/** bind a single external address to a cosmos id 


 *
 */

cosmos_id_t cosmos_bind_by_protocol( struct cosmos *cm, cosmos_id_t dest, char *protocol, char *addr, cosmos_id_t context)
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



        dc = dcel_new( NULL );

        dc->module_id = cosmos_put_string( cm, protocol );
        dc->addr = cosmos_put_string( cm, addr );


        /* todo: improve dcel_release to dispose of 0-retained objects. */

        dcel_release( dest->dcel );

        dest->dcel = dc;
        dcel_retain( dc );



        return dest;

abort:
        return COSMOS_ID_NULL;

}


cosmos_id_t cosmos_bind( struct cosmos *cm, cosmos_id_t dest, char *url, cosmos_id_t access_context)
{
        int i;
        size_t plen;
        char c, *prtcol, *addr;
        cosmos_id_t res;

        if( url == NULL )
        {
                HIERR("cosmos_bind: err: input addr NULL");

                return NULL;
        }




        /* parse url */

        if(url == NULL)
        {
                HIERR("cosmos_bind: url NULL");
                return COSMOS_ID_NULL;
        }
        
        for(i=0; (c=url[i])!=':'
               && c!='/'
               && plen++;
            i++);

        if(c == '/')
                goto default_protocol;

        prtcol = strndup(url,plen);

        if(url[i] == '/'
        && url[i+1] == '/')
        {
                addr = &(url[i+2]);
        }


        res = cosmos_bind_by_protocol( cm, dest, prtcol, addr, access_context);


        goto finish;

default_protocol:

        res = cosmos_bind_by_protocol( cm, dest, "file", addr, access_context);


finish:

        free(prtcol);
        
        return res;
}


cosmos_id_t cosmos_cascade_bind( struct cosmos *cm, cosmos_id_t af, cosmos_id_t af2 )
{

        if( af == NULL )
        {
                HIERR("cosmos_cascade_bind: af NULL");
                return NULL;
        }

        af->cascade = af2;

        return af;
}


