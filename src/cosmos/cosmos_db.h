#ifndef _COSMOS_COSMOS_DB_H_
#define _COSMOS_COSMOS_DB_H_

#include <stdint.h>
#include "../btree_cpp.h"

typedef uint64_t cosmos_id_t;

struct hiena_dcel;
struct access_frame;


struct cosmos {
        btree_t *strings;
        btree_t *pathstrings;
        btree_t *aframes;
        btree_t *dcels;
};


cosmos_id_t cosmos_string_put(struct cosmos *, char *);

char *cosmos_string_get(struct cosmos *, cosmos_id_t );

cosmos_id_t cosmos_path_put( struct cosmos *, char * );

char *cosmos_path_get( struct cosmos *, cosmos_id_t );

cosmos_id_t cosmos_aframe_put(struct cosmos *, cosmos_id_t, struct access_frame * );

struct access_frame *cosmos_aframe_get(struct cosmos *, cosmos_id_t );

cosmos_id_t cosmos_dcel_put( struct cosmos *, struct hiena_dcel * );

struct hiena_dcel *cosmos_dcel_get( struct cosmos *, cosmos_id_t );




#endif /* !_COSMOS_COSMOS_DB_H_ */