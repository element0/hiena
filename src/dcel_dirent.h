#ifndef HIENA_DCEL_DIRENT_H
#define HIENA_DCEL_DIRENT_H

struct hiena_mapcel;

struct dcel_dirent
{
        char *d_name;
        char *prefix;
        char *suffix;
        struct hiena_mapcel *mc;
};

#endif /* HIENA_DCEL_DIRENT_H */
