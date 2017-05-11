#include "mfrag.h"
#include "frag.h"
#include "hiena_svc.h"
#include <stdlib.h>
#include <string.h>


#include "frag_fh.h"
#include "hiena_fh.h"

static void *frag_fh_new()
{
        struct frag_fh *fh;

        fh = malloc( sizeof( *fh ));
        memset( fh, 0, sizeof( *fh ));

        return (void *)fh;
}

static int frag_fh_cleanup( void *fh )
{
        if( fh == NULL )
                return 0;
        
        free( fh );

        return 0;
}


struct hiena_fh *frag_fh_open( struct hiena_frag *f )
{
        if( f == NULL )
                return NULL;

        struct hiena_fh *fh, mfh;
        struct frag_fh *ffh1, ffh2;
        struct hiena_frag *f1, f2;
        struct hiena_mfrag *mf;

        f1 = f;
        fh = hiena_fh_new();

        /* frag_svc_ops defined in frag_svc.c */
        fh->ops = &frag_svc_ops;
        fh->addr = (void *)f;

        ffh1 = (struct frag_fh *)frag_fh_new();
        ffh1->frag = f1;

ffh_open_loop:

        if( frag_is_container( f1 ))
        {
                f2 = frag_get_first_content( f1 );
                ffh2 = (struct frag_fh *)frag_fh_new();
                ffh2->frag = f2;
                ffh1->inner_fh = ffh2;
                ffh2->outer_fh = ffh1;

                f1 = f2;
                ffh1 = ffh2;
                goto ffh_open_loop;
        }

/* ffh_open_content: */

        mf = f1->mfrag;
        mfh = mfrag_fh_open( mf );

        ffh1->mfrag_fh = mfh;

        fh->fh = (void *)ffh1;
        
        return fh;
}

int frag_fh_close( struct hiena_fh *fh )
{
        if( fh == NULL )
                return 0;

        struct frag_fh *ffh, ffh0;

        ffh = fh->fh;
        ffh0 = NULL;

        mfrag_fh_close( ffh->mfrag_fh );

        while( ffh != NULL )
        {
                ffh0 = ffh->outer_fh;
                frag_fh_cleanup( ffh );
                ffh = ffh0;
        }
        hiena_fh_cleanup( fh );

        return 0;
}