#ifndef HIENA_MAPCEL_DIR_H
#define HIENA_MAPCEL_DIR_H


#include "mapcel.h"


#define MAPCEL_DIR_BLOCKSIZE 64
#define MAPCEL_DIR_BLOCK_CAPACITY 8


struct mapcel_dir {
        int cur_i;
        int arr_dim;
        size_t arr_size;
        struct hiena_mapcel **arr;
};


struct mapcel_dir *mapcel_dir_new();

int mapcel_dir_cleanup(struct mapcel_dir *);

int mapcel_dir_add(struct mapcel_dir *, struct hiena_mapcel *);



#endif /* !HIENA_MAPCEL_DIR_H */