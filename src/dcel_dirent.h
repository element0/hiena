/** @file dcel_dirent.h */

#ifndef HIENA_DCEL_DIRENT_H
#define HIENA_DCEL_DIRENT_H

struct hiena_mapcel;

struct dcel_dirent
{
        char *d_name;
        char *prefix;
        char *suffix;

        struct hiena_dcel *dcel;

        /** next dirent */

        struct dcel_dirent *next;

        /** next homogenous dirent (of the same type) */

        struct dcel_dirent *next_homo;
};

#endif /* HIENA_DCEL_DIRENT_H */
