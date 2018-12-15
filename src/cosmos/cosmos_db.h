#ifndef _COSMOS_DB_H_
#define _COSMOS_DB_H_

#include <sys/types.h>
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

        char *metadirname;

        char *modrelpath;
        char *moddirpath;
        char *modsuffix;
        char **modsymbols;

        char *host_etcdir_fpath;
        char *host_libdir_fpath;

        char *host_lookupmod_fpath;
        char *host_svcmod_fpath;


        char *lookupmodname;

        char *svcmodname;

        size_t moddirpathlen;
        size_t modsuffixlen;

        char *proto_metadir_src_url;
        char *root_src_url;


        /* init */
        void *lookup_dl;
        void *filesvc;
        void *cosmsvc;
        void *lookupmod;
        struct access_frame *init;
        struct access_frame *base_svc;


        /* runtime */
        btree_t *strings;
        btree_t *paths;
	btree_t *vm;
        struct access_frame *proto;
        struct access_frame *root;


        /* maybe not */
        struct access_frame *openfiles;
        struct hiena_dcel *dcel;
        struct hiena_dcel *dcel_garbage;
};


struct cosmos *cosmos_db_new();


/**
 error code: 0) OK  no other error
 */
int cosmos_db_cleanup( struct cosmos * );



cosmos_strid_t cosmos_hash( char * );

cosmos_id_t cosmos_path_put( struct cosmos *, char * );

char *cosmos_path_get( struct cosmos *, cosmos_id_t );

struct hiena_dcel *cosmos_dcel_new( struct cosmos * );


/* maybe not */
cosmos_id_t cosmos_dcel_put( struct cosmos *, struct hiena_dcel * );

struct hiena_dcel *cosmos_dcel_get( struct cosmos *, cosmos_id_t );




#endif /* !_COSMOS_DB_H_ */
