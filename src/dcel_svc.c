
#include "hierr.h"
#include "dcel.h"
#include "dcel_fh.h"
#include "dcel_svc.h"
#include "frag.h"
#include "frag_svc.h"
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
        struct frag_fh *ffh, mapffh;
        struct hiena_mapcel *cur_mc;
        struct map_anchor *cur_ma;
        struct frag_curs *fcurs;

        dc = (struct hiena_dcel *)p;
        dfh = malloc(sizeof(*dfh));
        cur_f = dc->frag;
        ffh = frag_svc_open( (void *)cur_f, mode );
        mapffh = frag_mapsvc_open( (void *)cur_f, mode );
        cur_f = mapffh->frag;
        cur_ma = cur_f->head_anchor;
        fcurs = frag_curs_new( cur_f );

        if(mapffh->frag != ffh->frag)
        {
                HIERR("dcel_svc_open: warning: mapffh->frag != ffh->frag");
        }

        if( cur_ma == NULL )
        {
                cur_ma = malloc(sizeof(*cur_ma));
                cur_f->head_anchor = cur_ma;
        }

        dcel_retain( dc );

        dfh->dcel = dc;
        dfh->frag_fh = ffh;
        dfh->mapffh = mapffh;
        dfh->ma = cur_ma;
        dfh->fpos = 0;
        dfh->mapops = &dcel_mapsvc_ops;
        dfh->ops = &dcel_svc_ops;
        
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
        void *ffh;

        dfh = (struct dcel_fh *)p;
        ffh = dfh->frag_fh;

        frag_svc_close( ffh );

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
        ffh = dfh->frag_fh;

        c = frag_svc_ops.getchar( ffh );

        return c;
}

struct hiena_svc dcel_svc_ops = {
        .open = dcel_svc_open,
        .close = dcel_svc_close,
        .getchar = dcel_svc_getc
};




