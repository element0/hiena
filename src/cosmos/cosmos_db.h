#ifndef _COSMOS_DB_H_
#define _COSMOS_DB_H_

#include <stdint.h>
#include "../btree_cpp.h"
#include "cosmos_id.h"
#include "cosmos_string_db.h"
#include "cosmos_path_node.h"


struct hiena_dcel;
struct access_frame;


/**
  @param aframe cosmos db root aframe
  @param dcel   cosmos db root dcel
 */
struct cosmos {

        /* config */
        char *modlibpath;
        size_t modlibpathlen;
        char *modsuffix;
        size_t modsuffixlen;
     

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
        struct access_frame *root;
        struct access_frame *openfiles;
        struct hiena_dcel *dcel;

        /* maybe not */
        struct hiena_dcel *dcel_garbage;
};


struct cosmos *cosmos_db_new();

int cosmos_db_cleanup( struct cosmos * );

cosmos_id_t cosmos_bind(
    struct cosmos *cm,
    cosmos_id_t dest,
    char *protocol,
    char *addr,
    cosmos_id_t context);

cosmos_id_t cosmos_bind_uri(
    struct cosmos *cm,
    cosmos_id_t targ,
    char *addr,
    cosmos_id_t context);

cosmos_strid_t cosmos_hash( char * );

cosmos_id_t cosmos_path_put( struct cosmos *, char * );

char *cosmos_path_get( struct cosmos *, cosmos_id_t );

struct hiena_dcel *cosmos_dcel_new( struct cosmos * );


/* maybe not */
cosmos_id_t cosmos_dcel_put( struct cosmos *, struct hiena_dcel * );

struct hiena_dcel *cosmos_dcel_get( struct cosmos *, cosmos_id_t );




#endif /* !_COSMOS_DB_H_ */
