
#include <stdlib.h>
#include <string.h>
#include "cosmos_db.h"
#include "../btree_cpp.h"
#include "../hash.h"
#include "../hierr.h"
#include "../access_frame.h"

struct hiena_dcel;

struct cosmos *cosmos_db_new()
{
        struct cosmos *cm;
        cm = malloc(sizeof(*cm));
        memset(cm,0,sizeof(*cm));
        return cm;
}

int cosmos_db_cleanup(struct cosmos *cm)
{
        if(cm == NULL)
                return 0;

        free(cm);

        return 0;
}


cosmos_id_t cosmos_hash( char *s )
{
        return (cosmos_id_t)hash_sdbm(s);
}



cosmos_id_t cosmos_string_put(struct cosmos *cm, char *s)
{
        if(cm == NULL)
        {
                HIERR("cosmos_string_put: err cosmos object NULL");
                return 0;
        }
        cosmos_id_t id;
        btree_t *strings;

        strings = cm->strings;
        if( strings == NULL )
        {
                strings=btree_new();
                cm->strings=strings;
        }

        id = (cosmos_id_t)hash_sdbm(s);
        btree_put(strings, (bkey_t)id, (void *)s);

        return id;
}



char *cosmos_string_get(struct cosmos *cm, cosmos_id_t id )
{
        if(cm == NULL)
        {
                HIERR("cosmos_string_get: err cosmos object NULL");
                return NULL;
        }
        char *s;
        btree_t *strings;

        strings = cm->strings;
        if( strings == NULL )
        {
                HIERR("cosmos_string_get: warn cosmos object->strings NULL");

                return NULL;
        }

        s = btree_get(strings, (bkey_t)id);

        return s;
}




cosmos_id_t cosmos_path_put( struct cosmos *cm, char *s )
{
        if(cm == NULL)
        {
                HIERR("cosmos_path_put: err cosmos object NULL");
                return 0;
        }
        cosmos_id_t id;
        btree_t *paths;

        paths = cm->paths;
        if( paths == NULL )
        {
                paths=btree_new();
                cm->paths=paths;
        }

        id = (cosmos_id_t)hash_sdbm(s);
        btree_put(paths, (bkey_t)id, (void *)s);

        return id;
}



char *cosmos_path_get( struct cosmos *cm, cosmos_id_t id)
{
        if(cm == NULL)
        {
                HIERR("cosmos_path_get: err cosmos object NULL");
                return NULL;
        }
        char *s;
        btree_t *paths;

        paths = cm->paths;
        if( paths == NULL )
        {
                HIERR("cosmos_pathstring_get: warn cosmos object->paths NULL");

                return NULL;
        }

        s = btree_get(paths, (bkey_t)id);

        return s;
}



cosmos_id_t cosmos_dcel_put( struct cosmos *cm, struct hiena_dcel *dc )
{
        if(cm == NULL)
        {
                HIERR("cosmos_dcel_put: err cosmos object NULL");
                return 0;
        }

        return NULL;
}



struct hiena_dcel *cosmos_dcel_get( struct cosmos *cm, cosmos_id_t id)
{
        if(cm == NULL)
        {
                HIERR("cosmos_dcel_get: err cosmos object NULL");
                return NULL;
        }

        return NULL;
}
