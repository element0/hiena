
#include "../../cosmos.h"
#include "../../access_frame.h"

struct hiena_dcel *cosmos_lookup_fn( struct cosmos *cm, struct access_frame *af, char *s )
{
        struct hiena_dcel *dc, *dc2;


        dc = af->dcel;
        dc2 = dcel_get_child(dc, s);


        return dc2;
}