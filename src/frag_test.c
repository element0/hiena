#include "hierr.h"
#include "frag.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
        int ret = 0;
        struct hiena_frag *f = NULL;

        f = frag_new();

        if( f == NULL )
        {
                ret = -1;
                HIERR("err new_frag, abort tests");
                goto end;
        }



cleanup:
        frag_cleanup( f );
end:
        return ret;
}