#ifndef HIENA_DCEL_DIRHANDLE_H
#define HIENA_DCEL_DIRHANDLE_H






#include "dcel.h"




struct dcel_dirh {
        struct hiena_dcel *dcel;
        size_t pos, len, len_rem;
        struct cur_anchor;
};





#endif /* ! HIENA_DCEL_DIRHANDLE_H */
