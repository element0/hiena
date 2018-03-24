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
        struct access_frame *base_svc;

        /* runtime */
        btree_t *strings;
        btree_t *paths;
        struct access_frame *proto;
        struct access_frame *aframe;
        struct hiena_dcel *dcel;

        /* maybe not */
        struct hiena_dcel *dcel_garbage;
};


struct cosmos *cosmos_db_new();
int cosmos_db_cleanup( struct cosmos * );

cosmos_id_t cosmos_put_string(struct cosmos *, char *);

char *cosmos_get_string(struct cosmos *, cosmos_id_t );

int cosmos_release_string( struct cosmos *, cosmos_id_t, char * );

cosmos_id_t cosmos_string_id( char * );

cosmos_id_t cosmos_hash( char * );

cosmos_id_t cosmos_path_put( struct cosmos *, char * );

char *cosmos_path_get( struct cosmos *, cosmos_id_t );



struct hiena_dcel *cosmos_dcel_new( struct cosmos * );


/* maybe not */
cosmos_id_t cosmos_dcel_put( struct cosmos *, struct hiena_dcel * );

struct hiena_dcel *cosmos_dcel_get( struct cosmos *, cosmos_id_t );




#endif /* !_COSMOS_COSMOS_DB_H_ */
