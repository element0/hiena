#ifndef HIENA_PROD_INSTR
#define HIENA_PROD_INSTR

#include "context_frame.h"
#include "dcel.h"


struct prod_instr {
    void *context_frame;
    int argc;
    void **argv;
    void *prod_fn_guid;
    struct hiena_dcel *(*prod_fn)(
        struct context_frame *,
        int argc,
        void **argv);
};


#endif /* !HIENA_PROD_INSTR */