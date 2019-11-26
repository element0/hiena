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

        /** next dirent with the same d_name */

        struct dcel_dirent *next_same;
};

#endif /* HIENA_DCEL_DIRENT_H */
