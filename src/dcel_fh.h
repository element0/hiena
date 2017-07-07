#ifndef HIENA_DCEL_FH_H
#define HIENA_DCEL_FH_H











struct dcel_fh;

#include "hiena_svc.h"
#include "dcel.h"
#include "dcel_mapsvc.h"
#include "frag.h"
#include "frag_curs.h"
#include "mapcel.h"
#include "map_anchor.h"


struct dcel_fh {
        struct hiena_dcel *dcel;

        struct hiena_frag *frag;
        void *frag_fh;
        struct frag_curs *fcurs;

        struct hiena_mapcel *mc;
        struct map_anchor *ma;

        size_t pos;
        size_t fragpos;

        struct hiena_svc *ops;
        struct dcel_mapsvc_ops *mapops;

};




#endif /* !HIENA_DCEL_FH_H */