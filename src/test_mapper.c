#include <stdio.h>



void mapper_scan( dcel *dc )
{

}


int main( int argc, char *argv )
{
        dcel *dc = dcel_new( NULL ):

        dcel_assign_string( dc, "ssh://perfectworld.io/dandy.data" );

        mapper_scan( dc );

        dcel_debug_print_map( dc );

        dcel_cleanup( dc );

        return 0;
}