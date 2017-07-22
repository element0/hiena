#ifndef HIENA_DCEL_MAPSVC_H
#define HIENA_DCEL_MAPSVC_H


#include "dcel_fh.h"
#include "mapcel.h"
#include "dcel.h"


/*
    mapops:
     - seek( len )
     - new( ruleid, pos, len ) -> mc
     - add( mc, mc )
     - add_dirent( mc, mc )

     mc = mapcel
 */


int dcel_mapsvc_idcmp( void *, void * );


struct dcel_mapsvc_ops {

        struct hiena_mapcel *(*newterm)(struct dcel_fh *, int ruleid, size_t pos, size_t len);

        struct hiena_mapcel *(*new)(int ruleid);

        int (*add)( struct hiena_mapcel *parent, struct hiena_mapcel *child);

        int (*add_dirent)(struct hiena_mapcel *parent, struct hiena_mapcel *child);

};

struct dcel_mapsvc_ops dcel_mapsvc;



#endif /* ! HIENA_DCEL_MAPSVC_H */