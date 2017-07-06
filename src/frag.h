#ifndef _HIENA_FRAG_H_
#define _HIENA_FRAG_H_

#include <stdio.h>
#define HIFRAG_ERR(es) fprintf( stderr, "%s\n", es ), 1
#define HIFRAG_POS_T off_t
#define HIFRAG_BOUND_T off_t
#define HIFRAG_BOUNDS_MIN 0
#define HIFRAG_BOUNDS_MAX (2^31)
#define HIFRAG_POS_TO_HIMFRAG_BOUND(pos) pos



#include "btrees.h"
#include "mfrag.h"
#include "mapcel.h"
#include "map_anchor.h"



struct hiena_frag {
    btree_t *children;
    btree_t *anchors;
    struct hiena_mfrag *mfrag;
    struct map_anchor *head_anchor;
    struct map_anchor *tail_anchor;

    //---- old ----
    struct hiena_frag *first_content;
    struct hiena_frag *last_content;
    struct hiena_frag *prev;
    struct hiena_frag *next;
    void *userdata;
};


struct hiena_frag *frag_new();

int frag_cleanup( struct hiena_frag *f );


/*
 * frag map
 *
 */

#define frag_is_container( f ) f->mfrag == NULL

#define frag_has_room( f, off, len ) (( off + len ) < frag_get_length( f ))


int frag_insert( struct hiena_frag *, struct hiena_frag *, HIFRAG_POS_T );

struct map_anchor *frag_get_anchor( struct hiena_frag *, size_t pos );

int frag_set_anchor( struct hiena_frag *, size_t pos, struct map_anchor * );




struct hiena_frag *frag_child_contains_offset( struct hiena_frag *, size_t );


/*
 * media fragment
 *
 */

int frag_set_mfrag( struct hiena_frag *f, struct hiena_mfrag *mf );

struct hiena_mfrag *frag_get_mfrag( struct hiena_frag *f );

/*
 * user data
 *
 */

int frag_set_userdata( struct hiena_frag *, struct hiena_frag *prev  );


/*
 * meta data
 *
 */


HIFRAG_POS_T frag_get_length( struct hiena_frag *f );


/*---- old ----*/

int frag_set_first_content( struct hiena_frag *, struct hiena_frag *fc  );

struct hiena_frag *frag_get_first_content( struct hiena_frag *f );

int frag_set_last_content( struct hiena_frag *, struct hiena_frag *lc );

int frag_set_next( struct hiena_frag *, struct hiena_frag *next  );

struct hiena_frag *frag_get_next( struct hiena_frag *f );

int frag_set_prev( struct hiena_frag *, struct hiena_frag *prev  );



#endif /* !_HIENA_FRAG_H_ */