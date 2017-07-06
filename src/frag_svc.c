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
#include "hierr.h"

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
        struct frag_fh *ofh2;
        struct mfrag_fh *mfh;
        struct hiena_frag *nf;
        int c;

        if( fhp == NULL )
        {
                HIERR("frag_svc_getc: fhp is NULL");
                return -1;
        }

        fh  = (struct frag_fh *)fhp;
        ifh = fh->inner_fh;
        ofh = fh->outer_fh;

        if( ifh == NULL )
        {
                HIERR("frag_svc_getc: err: initial inner fh is NULL.");
                return EOF;
        }

        if( ofh == NULL )
        {
                HIERR("frag_svc_getc: warning: initial outer fh is NULL.");
        }



ffh_getc_loop:

        mfh = ifh->mfrag_fh;

        if( mfh == NULL )
        {
                HIERR("frag_svc_getc: warning: unexpected mfh NULL");
                goto ffh_step_out;
        }

        c = mfrag_svc_getc( (void *)mfh );

        if( c != EOF )
                return c;

        /* goto ffh_step_next; */



ffh_step_next:

        if( ifh->frag == NULL )
        {
                HIERR("frag_svc_getc:ffh_step_next: err: ifh->frag NULL");
                return EOF;
        }

        nf = ifh->frag->next;
        if( nf == NULL )
                goto ffh_step_out;

        nfh = frag_svc_open( nf, ifh->mode );
        if( nfh == NULL )
        {
                HIERR("frag_svc_getc: err: nfh = frag_svc_open(nf,mode) returned NULL");
                return EOF;
        }

        nfh->outer_fh = ifh->outer_fh;


        if( ifh == fh )
                HIERR("frag_svc_getc: warning: unexpected ifh==ofh");
        else
                frag_svc_close( ifh );

        ifh = nfh->inner_fh;

        nfh = NULL;

        fh->inner_fh = ifh;

        goto ffh_getc_loop;


ffh_step_out:


        if(ifh == ofh)
        {
                fh->inner_fh = ifh;
                return EOF;
        }

        ofh2 = ifh->outer_fh;
        if( ofh2 == NULL )
        {
                HIERR("frag_svc_getc: err: ofh2 NULL");
                return EOF;
        }
        frag_svc_close( ifh );

        ifh = ofh2;
        fh->inner_fh = ifh;

        goto ffh_step_next;
}


void *frag_svc_open( void *fp, const char *mode )
{
        if( fp == NULL
         || mode == NULL )
                return NULL;

        struct hiena_frag *f;
        struct frag_fh *fh;
        struct frag_fh *fh1, *fh2;
        struct hiena_frag *f1, *f2;
        struct hiena_mfrag *mf;
        struct mfrag_fh *mfh;

        f1 =(struct hiena_frag *)fp;


        /* root fh outer refs self
         */
        fh = frag_fh_new();
        fh->frag = f1;
        fh->outer_fh = fh;
        fh->inner_fh = NULL;
        fh->mode = mode;

        fh1 = fh;

ffh_open_loop:

        if( frag_is_container( f1 ))
        {
                f2 = frag_get_first_content( f1 );
                if( f2 == NULL ) {
                        HIERR("frag_svc_open: f2 NULL");
                        return NULL;
                }
                fh2 = frag_fh_new();
                fh2->frag = f2;
                fh2->outer_fh = fh1;
                fh2->inner_fh = NULL;
                fh2->mode = mode;

                fh1->inner_fh = fh2;
                fh1 = fh2;
                f1 = f2;

                goto ffh_open_loop;
        }

/* ffh_open_content: */

        mf = f1->mfrag;
        if(mf == NULL)
        {
                 HIERR("frag_svc_open: mf NULL");
                  return NULL;
        }
        mfh = mfrag_svc_open( mf, mode );

        fh1->mfrag_fh = mfh;
        fh1->frag = f1;

        /* inner_fh can potentially
           ref self OK.
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
        {
                mfrag_svc_close(ffh->mfrag_fh );

        while( ffh != fh )
        {
                ffh0 = ffh->outer_fh;
                frag_fh_cleanup( ffh );
                ffh = ffh0;
        }

        }
        frag_fh_cleanup( fh );

        return 0;
}