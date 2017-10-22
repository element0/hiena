#ifndef _HIENA_DCEL_H_
#define _HIENA_DCEL_H_



#include "frag.h"
#include "mapcel.h"
#include "btrees.h"


#define dcel_retain( dc ) dc->retain++

#define dcel_release( dc ) dc->retain--

/**
    @param index a btree.  keys are ruleids.  values are btrees.  the value btrees are keyed with ruleid values.  the values at the keys are dcel ptrs.

    index[ruleid]
        index[value]
            ptrlist[]

 */

struct hiena_dcel {
        struct hiena_frag *frag;
        struct hiena_mapcel *mapcel;
        int retain;
        btree_t *dircache;
        btree_t *index;
};

struct hiena_dcel *dcel_new( struct hiena_dcel * );
int dcel_cleanup( struct hiena_dcel * );

#endif /*! _HIENA_DCEL_H_ */
