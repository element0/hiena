#include <stdio.h>
#include "mapcel.h"
#include "mapcel_dir.h"

void main()
{
        struct hiena_mapcel m;
        struct mapcel_dir *d;
        int i;

        d = mapcel_dir_new();

        for( i=0; i<100; i++ )
        {
                //printf("i:%d\n",i);
                mapcel_dir_add(d,&m);
        }

        printf("mapcel_dir_test: alert: added %d elements to dirent array.\n", d->cur_i);

        mapcel_dir_cleanup(d);
}