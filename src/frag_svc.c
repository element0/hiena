#include <stdlib.h>
#include <string.h>
#include "hiena_fh.h"
#include "hiena_svc.h"
#include "mfrag.h"
#include "mfrag_fh.h"
#include "mfrag_svc.h"
#include "frag.h"
#include "frag_fh.h"
#include "frag_svc.h"

struct hiena_svc frag_svc_ops = {
        .read  = frag_svc_read,
        .write = frag_svc_write,
        .open  = frag_svc_open,
        .close = frag_svc_close,
        .seek  = frag_svc_seek,
        .getchar = frag_svc_getc,
};

size_t frag_svc_read( void *buf, size_t len, size_t n, void *fh )
{
        return 0;
}

size_t frag_svc_write( void *dst, size_t size, size_t nmemb, void *fh )
{
        return 0;
}


int frag_svc_seek( void *fh, long off, int whence )
{
        return -1;
}


int frag_svc_getc( void *fhp )
{
        struct frag_fh *fh, *nfh;
        struct frag_fh *ifh, *ofh;
        struct mfrag_fh *mfh;
        struct hiena_frag *nf;
        int c;

        fh  = (struct frag_fh *)fhp;
        ifh = fh;
        ofh = ifh->outer_fh;

ffh_getc_loop:

        mfh = ifh->mfrag_fh;

        if( mfh == NULL )
        {
                return EOF;
        }

        c = mfrag_svc_getc( (void *)mfh );

        if( c != EOF )
                return c;

        if( ofh == ifh )
                return EOF;

        mfrag_svc_close( mfh );

ffh_step_out:

        frag_svc_close( ifh );

        ifh = ofh;
        ofh = ifh->outer_fh;

        nf = ifh->frag->next;

        if( nf == NULL )
                goto ffh_step_out;

/* ffh_step_next: */
        
        nfh = frag_svc_open( nf, NULL );
        nfh->outer_fh = ofh;
        frag_svc_close( ifh );
        ifh = nfh;
        nfh = NULL;

        goto ffh_getc_loop;

        return EOF;
}


void *frag_svc_open( void *fp, const char *mode )
{
        if( fp == NULL )
                return NULL;

        struct hiena_frag *f;

        struct frag_fh *fh;
        struct frag_fh *fh1, *fh2;
        struct hiena_frag *f1, *f2;
        struct hiena_mfrag *mf;
        struct mfrag_fh *mfh;

        f = (struct hiena_frag *)fp;

        /* root fh outer refs self
         */
        fh = frag_fh_new();
        fh->frag = f;
        fh->outer_fh = fh;
        fh->inner_fh = NULL;

        fh1 = fh;
        f1  = f;

ffh_open_loop:

        if( frag_is_container( f1 ))
        {
                f2 = frag_get_first_content( f1 );
                fh2 = frag_fh_new();
                fh2->frag = f2;
                fh1->inner_fh = fh2;
                fh2->outer_fh = fh1;

                f1 = f2;
                fh1 = fh2;
                goto ffh_open_loop;
        }

/* ffh_open_content: */

        mf = f1->mfrag;
        mfh = mfrag_svc_open( mf, mode );
        fh1->mfrag_fh = mfh;

        /* inner_fh can potentially
           ref self.
         */
        fh->inner_fh = fh1;

        return fh;
}

int frag_svc_close( void *fhp )
{
        if( fhp == NULL )
                return 0;

        struct frag_fh *fh;
        struct frag_fh *ffh, *ffh0;

        fh = (struct frag_fh *)fhp;

        ffh  = fh->inner_fh;
        ffh0 = NULL;

        if( ffh != NULL )
                mfrag_svc_close(ffh->mfrag_fh );

        while( ffh != fh )
        {
                ffh0 = ffh->outer_fh;
                frag_fh_cleanup( ffh );
                ffh = ffh0;
        }
        frag_fh_cleanup( fh );

        return 0;
}