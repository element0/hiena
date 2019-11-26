#include <stdlib.h>
#include <string.h>
#include "mfrag.h"
#include "mfrag_fh.h"
#include "mfrag_svc.h"
#include "hiena_fh.h"
#include "hiena_svc.h"
#include "hierr.h"


struct hiena_svc mfrag_svc_ops = {
        .open  = mfrag_svc_open,
        .close = mfrag_svc_close,
        .seek  = mfrag_svc_seek,
        .read  = mfrag_svc_read,
        .write = mfrag_svc_write,
        .getchar = mfrag_svc_getc,
};



int mfrag_svc_getc( void *fhp )
{
        struct mfrag_fh *fh;
        struct hiena_mfrag *mf;
        void *srcfh;
        int c;


        if( fhp == NULL )
                return EOF;


        fh = (struct mfrag_fh *)fhp;

        if( fh->is_eof == 1 )
                return EOF;

        mf = fh->mfrag;

        if( mf != fh->mfrag_sav )
        {
                fprintf(stderr,"mfrag_svc_getc: mfrag_sav %lu, mfrag %lu\",fh->mfrag_sav,mf");
        }

        if( mf == NULL )
        {
                HIERR("mfrag_svc_getc: mf NULL");
                return EOF;
        }

        if( fh->pos > mf->boundtail
        || fh->pos < mf->boundhead )
        {
                fh->is_eof = 1;
                return EOF;
        }

        srcfh = fh->srcfh;
 
        c = mf->svc->getchar( srcfh );
        fh->pos++;

        return c;
}

int mfrag_svc_seek( void *fhp, long off, int whence )
{
        struct mfrag_fh *fh;

        fh = (struct mfrag_fh *)fhp;

        if( fh == NULL )
        {
                return HIERR( "mfrag_svc_seek: bad mfrag fh object" );
        }
        if( off > HIMFRAG_OFF_MAX || off < HIMFRAG_OFF_MIN )
        {
                return HIERR( "mfrag_svc_seek: outside limits" );
        }

        /* 2017-03-24 pos and off types should match */
        fh->pos += off;

        return 0;
}

size_t mfrag_svc_read( void *dst, size_t size, size_t n, void *fhp )
{
        struct mfrag_fh *fh;

        fh = (struct mfrag_fh *)fhp;

        if( fh == NULL )
        {
                return HIERR( "mfrag_fh_read: bad mfrag fh object" );
        }
        if( dst == NULL )
        {
                return HIERR( "mfrag_fh_read: bad dest buffer" );
        }
        if( ! HIMFRAG_SRC_VERIFY( fh ) )
        {
                return HIERR( "mfrag_io_read: bad src" );
        }
        return 0;
}

size_t mfrag_svc_write( void *buf, size_t size, size_t n, void *fh )
{
        return 0;
}


int mfrag_svc_flush( void *mfp );

void *mfrag_svc_open( void *mfp, const char *mode )
{
        if( mfp == NULL
         || mode == NULL )
                return NULL;


        struct hiena_mfrag *mf;
        struct mfrag_fh *fh;
        void *srcfh;

        mf = (struct hiena_mfrag *)mfp;
        fh    = mfrag_fh_new();
        srcfh = mf->svc->open( mf->addr, mode );
        mf->svc->seek( srcfh, mf->boundhead, SEEK_SET );
        
        fh->mfrag = mf;
        fh->srcfh = srcfh;
        fh->pos = mf->boundhead;
        fh->is_eof = 0;

        fh->mfrag_sav = mf;

        return (void *)fh;
}

int mfrag_svc_close( void *fhp )
{
        struct mfrag_fh *fh;
        struct hiena_mfrag *mf;
        void *srcfh;


        if( fhp == NULL )
                return 0;


        fh = (struct mfrag_fh *)fhp;
        srcfh = fh->srcfh;
        mf = fh->mfrag;

        if( srcfh != NULL )
        {
                mf->svc->close( srcfh );
                fh->srcfh = NULL;
        }

        mfrag_fh_cleanup( fh );

        return 0;
}


size_t mfrag_svc_append( struct mfrag_fh *fh, void *buf, size_t len );

size_t mfrag_svc_overwrite( struct mfrag_fh *fh, void *buf, size_t len );

off_t mfrag_svc_trim_tail( struct mfrag_fh *fh, off_t off );

off_t mfrag_svc_trim_head( struct mfrag_fh *fh, off_t off );


