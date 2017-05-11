








#include "frag_fh.h"

int main( )
{
        struct hiena_frag *f;
        struct hiena_fh *fh;

        f = new_frag();
        fh = frag_fh_open( f );
        frag_fh_close( fh );

        frag_fh_cleanup( fh );
        frag_cleanup( f );

        return 0;
}