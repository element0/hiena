#ifndef HIENA_DCEL_FH_H
#define HIENA_DCEL_FH_H











struct dcel_fh;

#include "btrees.h"
#include "hiena_svc.h"
#include "dcel.h"
#include "dcel_mapsvc.h"
#include "frag.h"
#include "frag_curs.h"
#include "mapcel.h"
#include "map_anchor.h"
#include "ptr_stack.h"


struct dcel_fh {
        struct hiena_dcel *dcel;
        size_t pos;

        struct hiena_frag *frag;
        size_t fragpos;
        void *frag_fh;
        struct frag_curs *fcurs;

        struct hiena_svc *ops;
        struct dcel_mapsvc_ops *mapops;

        /* directory builder */

        ptr_stack_t *dir_stack;

/* depricate? */

        btree_t *tmpdir;
        struct hiena_mapcel *mc;
        struct map_anchor *ma;

};




#endif /* !HIENA_DCEL_FH_H */