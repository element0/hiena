#ifndef _HIENA_FRAG_H_
#define _HIENA_FRAG_H_

#include <stdio.h>
#define HIFRAG_ERR(es) fprintf( stderr, "%s\n", es ), 1

#include "mfrag.h"


struct hiena_frag {
    struct hiena_mfrag *mfrag;
    struct hiena_frag *first_content;
    struct hiena_frag *last_content;
    struct hiena_frag *prev;
    struct hiena_frag *next;
    void *userdata;
};

struct hiena_frag *new_frag();

void frag_cleanup( struct hiena_frag *f );

int frag_set_first_content( struct hiena_frag *, struct hiena_frag *fc  );

int frag_set_last_content( struct hiena_frag *, struct hiena_frag *lc );

int frag_set_next( struct hiena_frag *, struct hiena_frag *next  );

int frag_set_prev( struct hiena_frag *, struct hiena_frag *prev  );

int frag_set_userdata( struct hiena_frag *, struct hiena_frag *prev  );

#endif /* !_HIENA_FRAG_H_ */