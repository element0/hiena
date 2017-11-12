#ifndef HIENA_PROD_INSTR
#define HIENA_PROD_INSTR

#include "access_frame.h"
#include "dcel.h"


struct prod_instr {
    void *prod_fn_guid;
    struct hiena_dcel *(*prod_fn)(
        struct access_frame *,
        int argc,
        void **argv);
    struct access_frame *aframe;
    int argc;
    void **argv;
};

struct hiena_dcel *prod_exec( struct prod_instr * );

struct prod_instr *prod_instr_new();

int prod_instr_cleanup( struct prod_instr * );

#endif /* !HIENA_PROD_INSTR */