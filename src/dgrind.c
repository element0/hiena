



#include "context_frame.h"
#include "dcel.h"
#include "slib.h"
#include "scanner.h"
#include "scanner_hdl.h"

struct hiena_dcel *dgrind( struct context_frame *cx, int argc, void **argv)
{
        char *hp, *sn;
        struct hiena_slib *slib;
        struct hiena_scanner *hs;
        struct hiena_dcel *dc;
        struct scanner_hdl *hsp;

        slib = argv[0];
        sn = argv[1];
        dc = argv[2];

        hs = slib_get_scanner(sn, slib);

        hsp = hsp_init_src_scanner_slib( dc, hs, slib );

        hs->op->parse( hsp );

        dc = hsp->res;

        hsp_cleanup( hsp );

        return dc;
}