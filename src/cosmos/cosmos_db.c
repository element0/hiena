
#include <stdlib.h>
#include <string.h>
#include "cosmos_db.h"
#include "../btree_cpp.h"
#include "../hash.h"
#include "../hierr.h"
#include "../access_frame.h"
#include "../dcel.h"

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
        struct access_frame *proto;

        if(cm == NULL)
                return 0;

        if(cm->lookup_dl != NULL)
                dlclose(cm->lookup_dl);

        proto = cm->proto;
        if(proto != NULL)
        {
                if(proto->lookfn_hdl != NULL)
                       aframe_cleanup(proto->lookfn_hdl);

                aframe_cleanup(proto);
        }

        


        free(cm);

        return 0;
}


cosmos_strid_t cosmos_hash( char *s )
{
        return (cosmos_strid_t)hash_sdbm(s);
}

cosmos_strid_t cosmos_string_id( char *s )
{
        return (cosmos_strid_t)hash_sdbm(s);
}



cosmos_strid_t cosmos_put_string(struct cosmos *cm, char *s)
{
        if(cm == NULL)
        {
                HIERR("cosmos_put_string: err cosmos object NULL");
                return 0;
        }
        cosmos_strid_t id;
        btree_t *strings;

        strings = cm->strings;
        if( strings == NULL )
        {
                strings=btree_new();
                cm->strings=strings;
        }

        id = (cosmos_strid_t)hash_sdbm(s);
        btree_put(strings, (bkey_t)id, (bval_t)s);

        return id;
}



char *cosmos_get_string(struct cosmos *cm, cosmos_strid_t id )
{
        if(cm == NULL)
        {
                HIERR("cosmos_get_string: err cosmos object NULL");
                return NULL;
        }


        char *s, *cmstr;
        btree_t *strings;



        strings = cm->strings;
        if( strings == NULL )
        {
                HIERR("cosmos_get_string: warn cosmos object->strings NULL");
                return NULL;
        }



        cmstr = (char *)btree_get(strings, (bkey_t)id);
        if( cmstr == NULL )
        {
                HIERR("cosmos_get_string: cmstr NULL");
                return NULL;
        }


        s = strdup( cmstr );
        if( s == NULL )
        {
                HIERR("cosmos_get_string: s NULL");
                return NULL;
        }


        return s;
}


int cosmos_release_string( struct cosmos *cm, cosmos_strid_t id, char *s )
{
        free(s);

        return 0;
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
        btree_put(paths, (bkey_t)id, (bval_t)s);

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

        s = (char *)btree_get(paths, (bkey_t)id);

        return s;
}


struct hiena_dcel *cosmos_dcel_new( struct cosmos *cm )
{
        if( cm == NULL )
        {
                HIERR("cosmos_dcel_new: err: cm NULL");
                return NULL;
        }

        struct hiena_dcel *dc;
        
        dc = dcel_new(cm->dcel_garbage);
        cm->dcel_garbage = dc;

        return dc;
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
