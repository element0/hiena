




#ifndef HIENA_FRAG_CURS_H
#define HIENA_FRAG_CURS_H

#include "frag.h"
#include "frag_fh.h"


struct frag_curs
{
        struct frag_fh *root;
        struct frag_fh *cur;
        size_t pos;
};



struct frag_curs *frag_curs_new( struct hiena_frag * );

int frag_curs_cleanup( struct frag_curs * );


int frag_curs_step_inward( struct frag_curs * );

int frag_curs_step_outward( struct frag_curs * );


struct hiena_frag *frag_curs_find_deepest( struct frag_curs * );

struct hiena_frag *frag_curs_find_deepest_has_room( struct frag_curs *, size_t len );


int frag_curs_seek( struct frag_curs *, size_t len, int whence);

int frag_curs_seek_into( struct frag_curs *, struct hiena_frag *, size_t off);

struct map_anchor *frag_curs_get_anchor( struct frag_curs * );



#endif /* ! HIENA_FRAG_CURS_H */