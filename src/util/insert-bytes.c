





#include <stdio.h>

#include "insert_bytes.h"


static void print_usage ( char *s )
{
        printf("%s SRCFILE STARTBYTE ENDBYTE DSTFILE AT_BYTE\n", s );
        printf("example: %s insertthis.txt 100 300 intothisat.txt 15", s );
}


int NEW_main( int argc, char *argv[] )
{
        struct hiena_dcel *dc[3];

        cx = context_frame_init();

        dc[0] = dsource(cx, 1, (void **)argv[1]);

        dc[1] = dsource(cx, 1, (void **)argv[4]);

        void *cmd[]={
            insert_bytes,
            dc[0],
            atoi(arg[2]),
            atoi(arg[3]),
            dc[1],
            atoi(arg[5])
        };

        dc[2] = dgrind(cx, 1, cmd);
}

/*   grinding with a shell command

        void *cmd[]={
            dgrind_shell,
            "insert_bytes",
            dcel_guid_str(dc[0]),
            arg[2],
            arg[3],
            dcel_guid_str(dc[1]),
            arg[5]
        };

*/


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
