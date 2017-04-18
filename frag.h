#ifndef _HIENA_FRAG_H_
#define _HIENA_FRAG_H_

#include <stdio.h>
#define HIFRAG_ERR(es) fprintf( stderr, "%s\n", es ), 1
#define HIFRAG_POS_T off_t
#define HIFRAG_BOUND_T off_t
#define HIFRAG_BOUNDS_MIN 0
#define HIFRAG_BOUNDS_MAX (2^31)
#define HIFRAG_POS_TO_HIMFRAG_BOUND(pos) pos

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

int frag_insert( struct hiena_frag *, struct hiena_frag *, HIFRAG_POS_T );

#endif /* !_HIENA_FRAG_H_ */