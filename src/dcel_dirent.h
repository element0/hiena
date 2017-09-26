#ifndef HIENA_DCEL_DIRENT_H
#define HIENA_DCEL_DIRENT_H

#include "mapcel.h"

struct dcel_dirent
{
        char *d_name;
        struct hiena_mapcel *mc;
};

#endif /* HIENA_DCEL_DIRENT_H */
