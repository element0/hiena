#ifndef HIENA_PROD_INSTR
#define HIENA_PROD_INSTR

#include <stdint.h>
#include "access_frame.h"
#include "dcel.h"


#define PRODFN_T(fnname) struct hiena_dcel *(*fnname)(struct access_frame *, int, void **)

typecast uintptr_t prodfn_guid_t;


struct prod_instr {
    prodfn_guid_t prodfn_guid;
    PRODFN_T(prod_fn);
    struct access_frame *aframe;
    int argc;
    void **argv;
};

struct hiena_dcel *prod_exec( struct prod_instr * );

struct prod_instr *prod_instr_new();

int prod_instr_cleanup( struct prod_instr * );

#endif /* !HIENA_PROD_INSTR */