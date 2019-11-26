







#include "mfrag.h"
#include "frag.h"
#include "frag_fh.h"

int main( )
{
        struct frag_fh *fh;
        struct hiena_frag *f;

        f = frag_new();

        fh = frag_fh_new( f );
        frag_fh_cleanup( fh );

        frag_cleanup( f );

        return 0;
}