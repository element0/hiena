#ifndef HIENA_PROD_INSTR
#define HIENA_PROD_INSTR

#include <stdint.h>
#include "cosmos.h"
#include "dcel.h"
#include "prod_args.h"


#define PRODFN_T(fnname) struct hiena_dcel *(*fnname)(struct access_frame *, int, void **)

typedef uintptr_t prodfn_guid_t;




struct prod_sequence {
        size_t page_size;
        int num_pages;
        size_t count;  //instr count
        void **first;
        void **last;

        // malloc first to page size
        //   multiple of (void *)
};

struct prod_sequence *prod_seq_new( size_t );

int prod_seq_cleanup( struct prod_sequence * );

prod_seq_add( struct prod_sequence *, void * );


struct prod_instr {
    int function_id;
    cosmos_str_id_t module_id;
    struct prod_sequence **args;

    PRODFN_T(fnptr);
};



struct prod_instr *prod_instr_new();

int prod_instr_cleanup( struct prod_instr * );

int prod_instr_add_arg( struct prod_instr *, int, size_t, void * );


struct prod_arg {
        int type;
        size_t len;
        void *data;
};

struct prod_arg *prod_arg_new( int, size_t, void * );

int prod_arg_cleanup( struct prod_arg * );




struct hiena_dcel *prod_exec( struct prod_sequence * );



#endif /* !HIENA_PROD_INSTR */