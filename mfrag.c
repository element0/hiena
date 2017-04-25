





#include "mfrag.h"
#include "hierr.h"
#include <stdlib.h>
#include <string.h>

struct hiena_mfrag *new_mfrag()
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

        m2 = memcpy( mf, m2, sizeof(*mf) );

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

abort_badsrc:
        
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
                return HIERR( "frag_set_bounds: outside limits" );
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


int mfrag_set_src( struct hiena_mfrag *f, HIMFRAG_SRC_T src ) {
        if( f == NULL )
                return 1;
        if( HIMFRAG_SRC_VERIFY( src ) ){
                return HIERR( "mfrag_set_src can't verify src" );
        } 
        f->src = src;
        return 0;
}


int mfrag_set_svc( struct hiena_mfrag *f, struct hiena_svc_module *svc )
{
        if( f == NULL )
                return -1;
        
        f->svc = svc;
        return 0;
}


int mfrag_set_addr( struct hiena_mfrag *mf, struct hiena_svc_addr *sa )
{
        if( mf == NULL )
                return -1;

        mf->svcaddr = sa;
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

int mfrag_io_seek( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off )
{
        if( ! HIMFRAG_IO_VERIFY( mfio ) )
        {
                return HIERR( "mfrag_io_seek: bad mfrag io object" );
        }
        if( off > HIMFRAG_OFF_MAX || off < HIMFRAG_OFF_MIN )
        {
                return HIERR( "mfrag_io_seek: outside limits" );
        }

        /* 20170324 pos and off types should match */
        mfio->pos += off;

        return 0;
}

HIMFRAG_BUFSIZE_T mfrag_io_read( struct hiena_mfrag_io *mfio, void *dst, HIMFRAG_BUFSIZE_T size )
{
        if( ! HIMFRAG_IO_VERIFY( mfio ) )
        {
                return HIERR( "mfrag_io_read: bad mfrag io object" );
        }
        if( dst == NULL )
        {
                return HIERR( "mfrag_io_read: bad dest buffer" );
        }
        if( ! HIMFRAG_SRC_VERIFY( mfio ) )
        {
                return HIERR( "mfrag_io_read: bad src" );
        }
        return 0;
}

HIMFRAG_BUFSIZE_T mfrag_io_write( struct hiena_mfrag_io *mfio, HIMFRAG_BUFSIZE_T size );

HIMFRAG_BUFSIZE_T mfrag_io_append( struct hiena_mfrag_io *mfio, void *buf, HIMFRAG_BUFSIZE_T len );

HIMFRAG_BUFSIZE_T mfrag_io_overwrite( struct hiena_mfrag_io *mfio, void *buf, HIMFRAG_BUFSIZE_T len );

HIMFRAG_OFF_T mfrag_io_trim_tail( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off );

HIMFRAG_OFF_T mfrag_io_trim_head( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off );

int mfrag_io_flush( struct hiena_mfrag_io *mfio );

