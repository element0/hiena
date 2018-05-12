#ifndef HIENA_DCEL_DIRSVC_H
#define HIENA_DCEL_DIRSVC_H






#include "dcel_dirh.h"
#include "dcel.h"






struct dcel_dirsvc_ops {

        struct dcel_dirh *(*opendir)(struct hiena_dcel *);

        struct dcel_dirent *(*readdir)(struct dcel_dirh *);

        int (*closedir)(struct dcel_dirh *);

};

struct dcel_dirsvc_ops dcel_dirsvc;



#endif /* ! HIENA_DCEL_DIRSVC_H */
