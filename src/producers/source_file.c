#include <stdlib.h>
#include "../dcel.h"
#include "../frag.h"
#include "../mfrag.h"
#include "../access_frame.h"
#include "../file_svc.h"
#include "../hierr.h"

/**
 * accepts only one arg, an address.
 *
 *
 */

struct hiena_dcel *cosmos_source_fn( struct access_frame *af, int argc, void **argv)
{
        /* af ignored */


        if( argc != 1 )
        {
                HIERR("prod_fn dsource: argc != 1");
                return NULL;
        }


        if( argv == NULL )
        {
                HIERR("prod_fn dsource: argv NULL");
                return NULL;
        }


        struct hiena_dcel *dc;
        struct hiena_frag *f;
        struct hiena_mfrag *mf;
        void *addr;



        f = frag_new();
        if( f == NULL )
        {
                HIERR("source_file: frag_new NULL");
                return NULL;
        }


        mf = mfrag_new();
        if( mf == NULL )
        {
                HIERR("source_file: mfrag_new NULL");
                frag_cleanup(f);
                return NULL;
        }


        addr = argv[0];
        mfrag_set_addr( mf, addr );
        mfrag_set_svc( mf, &file_svc_ops );
        mfrag_set_bounds( mf, 0, get_filesize( (char *)addr ) );


        frag_set_mfrag( f, mf );


        dc = malloc(sizeof(*dc));
        memset(dc, 0, sizeof(*dc));
        dc->frag = f;


        return dc;
}
