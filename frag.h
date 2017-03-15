#ifndef _HIENA_FRAG_H_
#define _HIENA_FRAG_H_

#include <stdio.h>
#define HIFRAG_ERR(es) fprintf( stderr, "%s\n", es ), 1

#include <sys/types.h>
#define HIFRAG_BOUND_T off_t
#define HIFRAG_BOUNDS_MIN 0
#define HIFRAG_BOUNDS_MAX (2^31)

#include <stdlib.h>
#define HIFRAG_SRC_T void *
#define HIFRAG_SRC_VERIFY(src) (src != NULL)


struct hiena_frag {
    struct hiena_frag *prev;
    struct hiena_frag *next;
    struct hiena_frag *first_content;
    struct hiena_frag *last_content;
    HIFRAG_BOUND_T boundhead;
    HIFRAG_BOUND_T boundtail;
    HIFRAG_SRC_T   src;
};

struct hiena_frag *new_frag();
void frag_cleanup( struct hiena_frag *f );
int frag_set_bounds( struct hiena_frag *f, HIFRAG_BOUND_T bh, HIFRAG_BOUND_T bt );
int frag_set_src( struct hiena_frag *f, HIFRAG_SRC_T src );
struct hiena_frag *frag_split( struct hiena_frag *f, HIFRAG_BOUND_T pos );

#endif /* !_HIENA_FRAG_H_ */