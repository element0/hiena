#ifndef HIENA_PRODUCER_FUNCS_H
#define HIENA_PRODUCER_FUNCS_H

#include "context_frame.h"


/* the four producer functions */





struct hiena_dcel *dsource( struct context_frame *, int, void **);

struct hiena_dcel *dbind( struct context_frame *, int, void **);

struct hiena_dcel *dfind( struct context_frame *, int, void **);

struct hiena_dcel *dgrind( struct context_frame *, int, void **);


#endif /*! HIENA_PRODUCER_FUNCS_H */