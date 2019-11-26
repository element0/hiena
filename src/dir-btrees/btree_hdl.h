#ifndef HIENA_BTREE_HANDLE_H
#define HIENA_BTREE_HANDLE_H

#include "btrees.h"

struct btree_hdl
{
        bnode_t *root;

        /* comparison op */
        int (*lt)(void *, void *);
};


#endif /*! HIENA_BTREE_HANDLE_H */