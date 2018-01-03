#ifndef _COSMOS_COSMOS_DB_H_
#define _COSMOS_COSMOS_DB_H_

#include <stdint.h>
#include "../btree_cpp.h"


struct hiena_dcel;
struct access_frame;
typedef struct access_frame *cosmos_id_t;

/**
  @param aframe cosmos db root aframe
  @param dcel   cosmos db root dcel
 */
struct cosmos {
        /* init */
        void *filesvc;
        void *cosmsvc;
        void *lookup;
        struct access_frame *init;

        /* runtime */
        btree_t *strings;
        btree_t *paths;
        struct access_frame *aframe;
        struct hiena_dcel *dcel;
};


struct cosmos *cosmos_db_new();
int cosmos_db_cleanup( struct cosmos * );

cosmos_id_t cosmos_string_put(struct cosmos *, char *);

char *cosmos_string_get(struct cosmos *, cosmos_id_t );

cosmos_id_t cosmos_path_put( struct cosmos *, char * );

char *cosmos_path_get( struct cosmos *, cosmos_id_t );

cosmos_id_t cosmos_aframe_put(struct cosmos *, cosmos_id_t, struct access_frame * );

struct access_frame *cosmos_aframe_get(struct cosmos *, cosmos_id_t );

cosmos_id_t cosmos_dcel_put( struct cosmos *, struct hiena_dcel * );

struct hiena_dcel *cosmos_dcel_get( struct cosmos *, cosmos_id_t );




#endif /* !_COSMOS_COSMOS_DB_H_ */
