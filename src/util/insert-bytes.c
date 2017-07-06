





#include <stdio.h>

#include "insert_bytes.h"


static void print_usage ( char *s )
{
        printf("%s SRCFILE STARTBYTE ENDBYTE DSTFILE AT_BYTE\n", s );
        printf("example: %s insertthis.txt 100 300 intothisat.txt 15", s );
}



int main( int argc, char *argv[] )
{
        if( argc != 6 )
        {
                print_usage( argv[0] );
                return -1;
        }
        struct hiena_frag *f;
        int ret;

        f = insert_bytes( argc, argv );
        return 0;
}
