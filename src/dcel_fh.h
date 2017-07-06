#ifndef HIENA_DCEL_FH_H
#define HIENA_DCEL_FH_H



#include "dcel.h"
#include "dcel_svc.h"
#include "dcel_mapsvc.h"
#include "frag.h"
#include "fragcurse.h"
#include "mapcel.h"
#include "map_anchor.h"
#include "hiena_svc.h"





struct dcel_fh {
        struct hiena_dcel *dcel;
        struct hiena_frag *frag;
        void *frag_fh;

        struct fragcurs *fcurs;
        struct map_anchor *ma;
        size_t fpos;
        size_t fragpos;
        struct hiena_mapcel *mc;

        struct dcel_mapsvc_ops *mapops;
        struct hiena_svc *ops;

};




#endif /* !HIENA_DCEL_FH_H */