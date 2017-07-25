#include "dcel_dirsvc.h"








struct dcel_fh *opendir( struct hiena_dcel *);

int closedir( struct dcel_fh * );

struct dirent *readdir( struct dcel_fh *);

struct dcel_mapsvc_ops dcel_dirsvc = {
};