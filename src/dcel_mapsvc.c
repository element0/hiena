





#include <stdlib.h>
#include "frag.h"
#include "frag_curs.h"
#include "dcel_fh.h"
#include "dcel_mapsvc.h"
#include "mapcel.h"
#include "hierr.h"
#include "btrees.h"


int dcel_mapsvc_idcmp( void *, void * );


struct hiena_mapcel *dcel_mapsvc_new(struct dcel_fh *dfh, int ruleid, size_t pos, size_t len)
{
        if( dfh == NULL )
        {
                HIERR("dcel_mapsvc_put: err: dfh is NULL");
                return NULL;
        }

        struct frag_curs *fc;
        struct hiena_mapcel *mc;
        struct map_anchor *mh;
        struct map_anchor *mt;


        fc = dfh->fcurs;
        //----------
        if( fc == NULL )
        {
                HIERR("dcel_mapsvc_put: err: dcel file handle's map cursor is NULL");
                return NULL;
        }

        if( frag_curs_step_deepest_has_room( fc, len ) != 0 )
        {
                HIERR("dcel_mapsvc_put: err: mapping out of bounds for dcel");
                return NULL;
        }


        mc = mapcel_new((int)rule_id, len);

        if( mc == NULL )
        {
                HIERR("dcel_mapsvc_put: err: can't make new mapcel");
                return NULL;
        }


        mh = frag_curs_get_anchor( fc );
        //----------
        if( mh == NULL )
        {
                HIERR("dcel_mapsvc_put: err: can't get head anchor");
                goto abort_mapcel;
        }

        frag_curs_seek( fc, len, SEEK_CUR );
        //----------
        mt = frag_curs_get_anchor( fc );

        if( mt == NULL )
        {
                HIERR("dcel_mapsvc_put: err: can't get tail anchor");
                map_anchor_cleanup( mh );
                goto abort_mapcel;
        }

        mapcel_set_head_anchor( mc, mh );

        mapcel_set_tail_anchor( mc, mt );

        return mc;

abort_mapcel:
        mapcel_cleanup( mc );
        return NULL;
}


int dcel_mapsvc_grow(void *p, size_t len)
{
        if( p == NULL )
        {
                HIERR("dcel_mapsvc_grow: err: p is NULL");
                return -1;
        }
        return 0;
}

int dcel_mapsvc_add(struct dcel_fh *dfh, struct hiena_mapcel *par, struct hiena_mapcel *chi);

struct dcel_mapsvc_ops dcel_mapsvc_ops = {
        .new = dcel_mapsvc_new,
        .add = dcel_mapsvc_add,
};