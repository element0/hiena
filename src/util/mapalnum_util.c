

#include <stdio.h>
#include <stdlib.h>
#include "mapalnum.h"
#include "../context_frame.h"
#include "../dcel.h"
#include "../prod_fns.h"
#include "../prod_args.h"
#include "../hierr.h"




int main( int argc, char *argv[])
{
        if( argc != 2 )
        {
                HIERR("mapalnum:main err: argc != 2");
        }

        struct hiena_dcel *dc;
        struct context_frame *cx;
        void *args[1];

        cx = context_frame_init();

        args[0] = (void *)argv[1];

        dc = dsource( cx, 1, args );

        mapalnum( dc );

        dcel_cleanup( dc );
        context_frame_cleanup( cx );

        return 0;
}
