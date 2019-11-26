







#include <stdio.h>
#include "mapcel.h"
#include "hierr.h"


int main( int argc, char *argv )
{
        struct hiena_mapcel *mc;
        int er;

        mc = mapcel_new(1, 2896);
        if( mc == NULL )
        {
               HIERR("mapcel_test: mapcel_new returns NULL.");
               return -1;
        }

        er = mapcel_cleanup( mc );

        return 0;
}