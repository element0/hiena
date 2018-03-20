#ifndef HIENA_PROD_INSTR
#define HIENA_PROD_INSTR

#include <stdint.h>
#include "access_frame.h"
#include "dcel.h"


#define PRODFN_T(fnname) struct hiena_dcel *(*fnname)(struct access_frame *, int, void **)

typedef uintptr_t prodfn_guid_t;


struct prod_instr {
    struct access_frame *module;
    struct access_frame *fnaf;
    PRODFN_T(fnptr);

    struct access_frame *aframe;
    int argc;
    void **argv;
};


struct hiena_dcel *prod_exec( struct prod_instr * );

struct prod_instr *prod_instr_new();

int prod_instr_cleanup( struct prod_instr * );

#endif /* !HIENA_PROD_INSTR */