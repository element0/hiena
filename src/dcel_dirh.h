#ifndef HIENA_DCEL_DIRHANDLE_H
#define HIENA_DCEL_DIRHANDLE_H






#include "dcel.h"
#include "frag_cursor.h"
#include "map_anchor.h"




struct dcel_dirh {
        struct hiena_dcel *dcel;
        struct frag_curs *frag_cursor;
        struct map_anchor *cur_mapanchor;
        size_t pos, len, len_rem;
};





#endif /* ! HIENA_DCEL_DIRHANDLE_H */
