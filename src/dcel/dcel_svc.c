
#include <stdlib.h>
#include "hierr.h"
#include "mapcel.h"
#include "map_anchor.h"
#include "frag.h"
#include "frag_fh.h"
#include "frag_svc.h"
#include "frag_curs.h"
#include "dcel.h"
#include "dcel_fh.h"
#include "dcel_svc.h"
#include "dcel_mapsvc.h"




void *dcel_svc_open( void *p, const char *mode )
{
        if( p == NULL
         || mode == NULL )
        {
                HIERR("dcel_svc_open: err: p or mode is NULL.");
                return NULL;
        }

        struct hiena_dcel *dc;
        struct dcel_fh *dfh;

        struct hiena_frag *cur_f;
        struct frag_fh *ffh;
        struct frag_curs *fcurs;

        struct hiena_mapcel *cur_mc;
        struct map_anchor *cur_ma;


        dc = (struct hiena_dcel *)p;
        dfh = malloc(sizeof(*dfh));

        cur_f = dc->frag;
        ffh = (struct frag_fh *)frag_svc_open( (void *)cur_f, mode );
        fcurs = frag_curs_new( cur_f );

        cur_mc = NULL;
        cur_ma = NULL;
        
        dcel_retain( dc );

        dfh->dcel = dc;
        dfh->frag = cur_f;
        dfh->frag_fh = ffh;
        dfh->fcurs = fcurs;
        dfh->mc = cur_mc;
        dfh->ma = cur_ma;
        dfh->pos = 0;
        dfh->fragpos = 0;
        dfh->ops = &dcel_svc_ops;
        dfh->mapops = &dcel_mapsvc;
        
        return (void *)dfh;
}

int dcel_svc_close( void *p )
{
        if( p == NULL )
        {
                HIERR("dcel_svc_close: err: p is null.");
        
                return -1;
        }

        struct dcel_fh *dfh;
        struct hiena_dcel *dc;

        struct hiena_frag *frag;
        void *ffh;
        struct frag_curs *fcurs;

        struct hiena_mapcel *mc;
        struct map_anchor *ma;
        ptr_stack_t dstack;


        dfh = (struct dcel_fh *)p;
        dc  = dfh->dcel;
        ffh = dfh->frag_fh;
        fcurs = dfh->fcurs;
        dstack = dfh->dir_stack;

        frag_svc_close( ffh );
        frag_curs_cleanup( fcurs );
        ptr_stack_cleanup( dstack );

        dcel_release( dc );

        free( dfh );

        return 0;
}

int dcel_svc_getc( void *p )
{
         if( p == NULL )
        {
                HIERR("dcel_svc_getc: err: p is null.");
                return -1;
        }
        struct dcel_fh *dfh;
        void *ffh;
        char c;

        dfh = (struct dcel_fh *)p;

        c = frag_svc_ops.getchar( dfh->frag_fh );

        return c;
}

struct hiena_svc dcel_svc_ops = {
        .open = dcel_svc_open,
        .close = dcel_svc_close,
        .getchar = dcel_svc_getc
};




