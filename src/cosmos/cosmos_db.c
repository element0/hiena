
#include <stdlib.h>
#include <string.h>
#include "cosmos_db.h"
#include "../btree_cpp.h"
#include "../hash.h"
#include "../dcel.h"
#include "../access_frame.h"


struct cosmos *cosmos_obj_new()
{
        struct cosmos *cm;
        cm = malloc(sizeof(*cm));
        memset(cm, sizeof(*cm));
        return cm;
}

int cosmos_obj_cleanup(struct cosmos *cm)
{
        if(cm == NULL)
                return 0;

        free(cm);

        return 0;
}




cosmos_id_t cosmos_string_put(struct cosmos *cm, char *s)
{
        if(cm == NULL)
        {
                HIERR("cosmos_string_put: err cosmos object NULL");
                return NULL;
        }
        cosmos_id_t id;
        btree_t *strings;

        strings = cm->strings;
        if( strings == NULL )
        {
                strings=btree_new();
                cm->strings=strings;
        }

        id = hash_sdbm(s);
        btree_put(strings, id, (void *)s);

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
                return NULL;
        }
        cosmos_id_t id;
        btree_t *pathstrings;

        pathstrings = cm->pathstrings;
        if( pathstrings == NULL )
        {
                pathstrings=btree_new();
                cm->pathstrings=pathstrings;
        }

        id = hash_sdbm(s);
        btree_put(pathstrings, id, (void *)s);

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
        btree_t *pathstrings;

        pathstrings = cm->pathstrings;
        if( pathstrings == NULL )
        {
                HIERR("cosmos_pathstring_get: warn cosmos object->pathstrings NULL");

                return NULL;
        }

        s = btree_get(pathstrings, (bkey_t)id);

        return s;
}




cosmos_id_t cosmos_aframe_put(struct cosmos *cm, struct access_frame *af)
{
        if(cm == NULL)
        {
                HIERR("cosmos_aframe_put: err cosmos object NULL");
                return NULL;
        }
        cosmos_id_t id;
        btree_t *aframes;

        aframes = cm->aframes;
        if( aframes == NULL )
        {
                HIERR("cosmos_aframe_put: warn cosmos object->aframes NULL");

                return NULL;
        }

        id = (bkey_t)af;
        btree_put(aframes, id, (void *)af);

        return id;
}




struct access_frame *cosmos_aframe_get(struct cosmos *cm, cosmos_id_t id)
{
        if(cm == NULL)
        {
                HIERR("cosmos_aframe_get: err cosmos object NULL");
                return NULL;
        }
        struct access_frame  *af;
        btree_t *aframes;

        aframes = cm->aframes;
        if( aframes == NULL )
        {
                HIERR("cosmos_aframe_get: warn cosmos object->aframes NULL");

                return NULL;
        }

        af = btree_get(aframes, (bkey_t)id);

        return af;
}



cosmos_id_t cosmos_dcel_put( struct cosmos *cm, struct hiena_dcel *dc )
{
        if(cm == NULL)
        {
                HIERR("cosmos_dcel_put: err cosmos object NULL");
                return NULL;
        }
        cosmos_id_t id;
        btree_t *dcels;

        dcels = cm->dcels;
        if( dcels == NULL )
        {
                HIERR("cosmos_dcel_put: warn cosmos object->dcels NULL");

                return NULL;
        }

        id = (bkey_t)dc;
        btree_put(dcels, id, (void *)dc);

        return id;
}



struct hiena_dcel *cosmos_dcel_get( struct cosmos *cm, cosmos_id_t id)
{
        if(cm == NULL)
        {
                HIERR("cosmos_dcel_get: err cosmos object NULL");
                return NULL;
        }
        struct hiena_dcel  *dc;
        btree_t *dcels;

        dcels = cm->dcels;
        if( dcels == NULL )
        {
                HIERR("cosmos_dcel_get: warn cosmos object->dcels NULL");

                return NULL;
        }

        dc = btree_get(dcels, (bkey_t)id);

        return dc;
}