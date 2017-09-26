#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "mapcel_dir.h"
#include "mapcel.h"
#include "hierr.h"

struct mapcel_dir *mapcel_dir_new()
{
        struct mapcel_dir *d;

        d = malloc(sizeof( *d ));
        memset(d,0,sizeof( *d ));

        return d;
}

int mapcel_dir_cleanup( struct mapcel_dir *d )
{
        if( d == NULL )
        {
                HIERR("mapcel_dir_cleanup: d NULL"); 
                return -1;
        }

        struct hiena_mapcel **a;

        a = d->arr;

        if( a != NULL )
        {
                free(a);
        }

        free(d);

        return 0;
}

int mapcel_dir_add( struct mapcel_dir *d, struct hiena_mapcel *mc )
{
        if( d == NULL
         || mc == NULL )
        {
                HIERR("mapcel_dir_add: err: d or mc NULL");
                return -1;
        }

        int i,k;
        size_t z,b;
        struct hiena_mapcel **a;
        void *r;

        i = d->cur_i;
        k = d->arr_dim;
        z = d->arr_size;
        b = MAPCEL_DIR_BLOCKSIZE;
        a = d->arr;

        if( a == NULL )
        {
                a = malloc(b);
                d->arr_dim = MAPCEL_DIR_BLOCK_CAPACITY;
                d->arr_size = b;
                d->arr = a;

                fflush(stdin);
                printf("malloc a\n");
                fflush(stdin);
        } else if( i >= k )
        {
                r = realloc(a,z+b);

                if( r == NULL )
                {
                        if( errno == ENOMEM )
                        {
                                HIERR("mapcel_dir_add: err: ENOMEM");
                                return -1;
                        }
                        HIERR("mapcel_dir_add: err: r NULL");
                        return -1;
                }
                a = r;
                d->arr = a;
                d->arr_dim += MAPCEL_DIR_BLOCK_CAPACITY;
                d->arr_size += b;

                fflush(stdin);
                printf("realloc a\n");
                fflush(stdin);
        }

        a[i] = mc;
        d->cur_i++;

        printf("%d\n",i);

        return 0;
}