#ifndef HIENA_DCEL_DIRSVC_H
#define HIENA_DCEL_DIRSVC_H






#include <dirent.h>
#include "dcel_fh.h"
#include "dcel.h"






struct dcel_dirsvc_ops {

        struct dcel_fh *(*opendir)(struct hiena_dcel *);

        struct dirent *(*readdir)(struct dcel_fh *);

        int (*closedir)(struct dcel_fh *);

};

struct dcel_dirsvc_ops dcel_dirsvc;



#endif /* ! HIENA_DCEL_DIRSVC_H */
