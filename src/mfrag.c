





#include "mfrag.h"
#include "hierr.h"
#include <stdlib.h>
#include <string.h>

struct hiena_mfrag *mfrag_new()
{
        struct hiena_mfrag *mf = malloc(sizeof( *mf ));
        return mf;
}

struct hiena_mfrag *mfrag_dup( struct hiena_mfrag *mf )
{
        if( mf == NULL )
                return NULL;


        struct hiena_mfrag *m2;
        void *buf;
        HIMFRAG_BUFSIZE_T bufsize;


        m2 = malloc( sizeof(*mf) );
        if( m2 == NULL )
                return NULL;

        m2 = memcpy( m2, mf, sizeof(*mf) );

        if( mf->buf != NULL )
        {
                bufsize = mf->bufsize;
                buf = malloc( bufsize );
                if( buf == NULL )
                {
                        HIERR( "mfrag_dup: can't malloc dup buffer" );
                        goto abort_badbuf;
                }else{
                        memcpy( buf, mf->buf, bufsize );
                }
        }


        return m2;

abort_badbuf:
        free( m2 );
        return NULL;
}

void mfrag_cleanup( struct hiena_mfrag *mf )
{
        if( mf != NULL )
                free( mf );
}


int mfrag_set_bounds( struct hiena_mfrag *f, HIMFRAG_BOUND_T bh, HIMFRAG_BOUND_T bt )
{
        if( f == NULL )
                return 1;
        if(( bh < HIMFRAG_BOUNDS_MIN ) || ( bh > HIMFRAG_BOUNDS_MAX ) ||
( bt < HIMFRAG_BOUNDS_MIN ) ||
( bt > HIMFRAG_BOUNDS_MAX )) {
                return HIERR( "mfrag_set_bounds: outside limits" );
        }
        f->boundhead = bh;
        f->boundtail = bt;
        return 0;
}


int mfrag_set_boundhead( struct hiena_mfrag *f, HIMFRAG_BOUND_T bh )
{
        if( f == NULL )
                return 1;
        if(( bh < HIMFRAG_BOUNDS_MIN ) || ( bh > HIMFRAG_BOUNDS_MAX )) {
                return HIERR( "frag_set_boundhead: outside limits" );
        }
        f->boundhead = bh;

        return 0;
}

int mfrag_set_boundtail( struct hiena_mfrag *f, HIMFRAG_BOUND_T bt )
{
        if( f == NULL )
                return 1;
        if(
( bt < HIMFRAG_BOUNDS_MIN ) ||
( bt > HIMFRAG_BOUNDS_MAX )) {
                return HIERR( "frag_set_boundtail: outside limits" );
        }

        f->boundtail = bt;
        return 0;
}


int mfrag_set_svc( struct hiena_mfrag *f, struct hiena_svc *svc )
{
        if( f == NULL )
                return -1;
        
        f->svc = svc;
        return 0;
}


int mfrag_set_addr( struct hiena_mfrag *mf, void *sa )
{
        if( mf == NULL )
                return -1;

        mf->addr = sa;
        return 0;
}

HIMFRAG_BOUND_T mfrag_get_length( struct hiena_mfrag *mf )
{
        if( mf == NULL )
                return 0;

        HIMFRAG_BOUND_T len;

        if( mf->boundtail > mf->boundhead )
        {
                len = mf->boundtail - mf->boundhead;
        } else {
                len = 0;
        }
        return len;
}

