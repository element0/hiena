#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "../access_frame.h"
#include "../btree_cpp.h"
#include "../hierr.h"
#include "../ptr_stack.h"
#include "cosmos_db.h"
#include "cosmos_dirh.h"
#include "cosmos_string_db.h"





cosmos_id_t cosmos_lookup(struct cosmos *cm, cosmos_id_t par, char *pathstr);





cosmos_id_t cosmos_lookup_bind(struct cosmos *cm, ptr_stack_t cascades, ptr_stack_t strstate )
{
        cosmos_id_t found, cur;

        while((cur = ptr_stack_pop(cascades)) != NULL)
                cosmos_lookup( cm, cur, ptr_stack_pop(strstate);

        return found;
}




static cosmos_id_t
cosmos_cache_lookup(struct cosmos *cm, cosmos_id_t par, char **cur, ptr_stack_t cascades, ptr_stack_t strstate, char *strtokstate)
{
        cosmos_strid_t key;
        cosmos_id_t found, last;
        btree_t *br;


        key = cosmos_string_id(cur);
        br = par->branch;
        found = (struct access_frame *)btree_get(br, (bkey_t)key);


        if( found != NULL )
        {
                printf("cosmos_cache_lookup cache branch %s\n", cur);

                *cur = strtok_r(NULL, "/", strtokstate);

                br = found->branch;

                last = found;


                /* journal cascade bind points */

                if(found->cascade != NULL)
                {
                        ssav = strndup(cur, strlen(cur));
                        ptr_stack_push(cascades, (void *)found);
                        ptr_stack_push(strstate, (void *)ssav);
                }
        }

        return found;
}



cosmos_id_t cosmos_lookup_cascade(struct cosmos *cm, cosmos_id_t par, char *pathstr)
{
        (struct access_frame *)par;
        cosmos_id_t found;


        for(; par != NULL && (found = cosmos_lookup( cm, par, pathstr)) == COSMOS_ID_NULL; par = par->parent);

        return found;
}




static cosmos_id_t cosmos_lookup_cache(struct cosmos *cm, cosmos_id_t par, char *pathstr)
{
        (struct access_frame *)par;
        cosmos_strid_t key;
        btree_t *br;

        printf("cosmos_lookup_cache for %s\n", cur);

        br = par->branch;
        key = cosmos_string_id(pathstr);

        return (struct access_frame *)btree_get(br, (bkey_t)key);
}

static cosmos_id_t cosmos_lookup_map(struct struct cosmos *cm, cosmos_id_t par, char *pathstr)
{
        (struct access_frame *)par;
        struct hiena_dcel *dc;
        struct access_frame *(*lookfn)(struct cosmos *, struct access_frame *, char *);
        
        
        if(par == NULL)
        {
                HIERR("cosmos_lookup_map: err: par NULL");
                return COSMOS_ID_NULL;
        }
        
        /* get lookup function */

        if((lookfn = par->lookfn) == NULL)
        {
                if( par->parent == NULL )
                {
                        HIERR("cosmos_lookup: err: par->parent NULL");
                        return COSMOS_ID_NULL;
                }
                lookfn = par->parent->lookfn;
        }

        if( lookfn == NULL )
        {
                HIERR("cosmos_lookup_map: err: lookfn NULL");
                return COSMOS_ID_NULL;
        }


        /* lookup in map */

        dc = par->dcel;
        if(dc == NULL)
        {
                HIERR("cosmos_lookup_map: alert: dcel NULL");
                return COSMOS_ID_NULL;
        }


        printf("cosmos_lookup_map run deligate func for %s\n", cur);

        /* TODO:  add sync check */
        if((found = lookfn(cm, par, pathstr)) == COSMOS_ID_NULL)
        {
                modname = cosmos_get_string( cm, dc->module_id );
                mapfnpath = cosmos_calc_fnpath( cm, modname, CM_MAP_FN_NAME);
                mapfn = cosmos_lookup_cascade( cm, par, mapfnpath );

                if(cosmos_exec_mapfn(cm, mapfn, par) == 0)
                        found = lookfn(cm, par, pathstr);
        }
        
        return found;
}




cosmos_id_t cosmos_lookup(struct cosmos *cm, cosmos_id_t par, char *pathstr)
{
        (struct access_frame *)par;


        cosmos_id_t found, last;
        char *ssav, *s, *cur, *fnpath, *modname, *strtokstate;
        size_t slen;

        ptr_stack_t cascades;
        ptr_stack_t strstate;


        if(par == NULL)
        {
                HIERR("cosmos_lookup: err: par NULL");

                return COSMOS_ID_NULL;
        }


        cascades = ptr_stack_new();
        strstate = ptr_stack_new();

        slen = strlen(pathstr);
        s = strndup(pathstr,slen);


        for(cur = strtok_r(s, "/", &strtokstate), last = par; cur != NULL; cur = strtok_r(NULL, "/", &strtokstate), last = found)
        {

                /* TODO: sync */


                if((found = cosmos_lookup_cache(cm,last,cur)) != COSMOS_ID_NULL
                || (found = cosmos_lookup_map(cm,last,cur)) != COSMOS_ID_NULL)
                {
                        /* journal cascade bind points */

                        if(found->cascade != NULL)
                        {
                                ssav = strndup(cur, strlen(cur));
                                ptr_stack_push(cascades, (void *)found);
                                ptr_stack_push(strstate, (void *)ssav);
                        }

                        continue;
                }



                /* keep this next assignment as a stub for when we add frame-relative lookup functions 

                found->lookfn = lookfn;
                */

                btree_put(br, (bkey_t)key, (bval_t)found);
        }

        free(s);
        ptr_stack_cleanup(cascades);
        ptr_stack_cleanup(strstate);

        /* memory TODO:  free the strings in strstate */

        return (cosmos_id_t)found;
}





