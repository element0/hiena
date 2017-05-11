#include "hierr.h"
#include "frag.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
        int ret = 0;
        struct hiena_frag *f = NULL;



        if(( f = new_frag() ) == NULL ) {
                ret = HIFRAG_ERR( "err new_frag, abort tests" );
                goto end;
        }



cleanup:
        frag_cleanup( f );
end:
        return ret;
}