#ifndef _HIENA_DFIND_H
#define _HIENA_DFIND_H

#include "context_frame.h"
#include "dcel.h"

struct hiena_dcel *dfind_child( struct context_frame *cx, int argc, void **argv);

struct hiena_dcel *dfind_prop( struct context_frame *cx, int argc, void **argv);


#endif
