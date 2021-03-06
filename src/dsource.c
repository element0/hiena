#include <stdlib.h>
#include "dcel.h"
#include "frag.h"
#include "mfrag.h"
#include "prod_instr.h"
#include "access_frame.h"
#include "file_svc.h"
#include "hierr.h"

/**
 * accepts only one source arg.
 *
 */

struct hiena_dcel *dsource( struct access_frame *af, int argc, void **argv)
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
        void *srca;
        struct prod_instr *pi;

        f = frag_new();

        if( f == NULL )
        {
                HIERR("dsource: frag_new NULL");
                return NULL;
        }

        mf = mfrag_new();

        if( mf == NULL )
        {
                HIERR("dsource: mfrag_new NULL");
                frag_cleanup(f);
                return NULL;
        }

        srca = argv[0];

        mfrag_set_addr( mf, srca );

        mfrag_set_svc( mf, &file_svc_ops );

        mfrag_set_bounds( mf, 0, get_filesize( (char *)srca ) );

        frag_set_mfrag( f, mf );

        dc = malloc(sizeof(*dc));
        memset(dc, 0, sizeof(*dc));

        dc->frag = f;

        return dc;

}
