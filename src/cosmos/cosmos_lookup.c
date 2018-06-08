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





cosmos_id_t cosmos_lookup_cascade(struct cosmos *cm, ptr_stack_t cascades, ptr_stack_t strstate )
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
}



cosmos_id_t cosmos_lookup_reverse(struct cosmos *cm, cosmos_id_t par, char *pathstr)
{
        (struct access_frame *)par;
        cosmos_id_t found, last;
        cosmos_id_t mapfn;
        cosmos_strid_t key;
        btree_t *br;
        char *ssav, *s, *cur, *fnpath, *modname;
        size_t slen;
        int err;
        ptr_stack_t cascades;
        ptr_stack_t strstate;
        char *strtokstate;


        if(par == NULL)
        {
                HIERR("cosmos_lookup: err: par NULL");

                return COSMOS_ID_NULL;
        }




        cascades = ptr_stack_new();
        strstate = ptr_stack_new();

        slen = strlen(pathstr);
        s = strndup(pathstr,slen);

        cur = strtok_r(s, "/", &strtokstate);
        br = par->branch;
        last = par;

        while(cur != NULL)
        {

                /* TODO: sync */


                /* begin cache lookup */

                

                        continue;
                }
                /* end cache lookup */


}






cosmos_id_t cosmos_lookup(struct cosmos *cm, cosmos_id_t par, char *pathstr)
{
        (struct access_frame *)par;

        struct access_frame *(*lookfn)(struct cosmos *, struct access_frame *, char *);

        struct hiena_dcel *dc;

        cosmos_id_t found, last;
        cosmos_id_t mapfn;
        cosmos_strid_t key;
        btree_t *br;
        char *ssav, *s, *cur, *fnpath, *modname, *strtokstate;
        size_t slen;
        int err;
        ptr_stack_t cascades;


        if(par == NULL)
        {
                HIERR("cosmos_lookup: err: par NULL");

                return COSMOS_ID_NULL;
        }


        cascades = ptr_stack_new();
        strstate = ptr_stack_new();

        slen = strlen(pathstr);
        s = strndup(pathstr,slen);

        br = par->branch;
        last = par;

        for(cur = strtok_r(s, "/", &strtokstate); cur != NULL; cur = strtok_r(NULL, "/", &strtokstate))
        {

                /* TODO: sync */


                /* lookup cache */

                key = cosmos_string_id(cur);

                found = (struct access_frame *)btree_get(br, (bkey_t)key);


                if( found != NULL )
                {
                        printf("cosmos_lookup cache branch %s\n", cur);

                        br = found->branch;
                        last = found;

                        /* journal cascade bind points */

                        if(found->cascade != NULL)
                        {
                                ssav = strndup(cur, strlen(cur));
                                ptr_stack_push(cascades, (void *)found);
                                ptr_stack_push(strstate, (void *)ssav);
                        }

                        continue;
                }

                /* end cache lookup */



                /* check if we need to run mapper */


                dc = par->dcel;

                /* TODO:  add sync check */
                if( dc != NULL && dc->child_list == NULL )
                {
                        /* run mapper */

                        modname = cosmos_get_string( cm, dc->module_id );
                        fnpath = cosmos_calc_fnpath( cm, modname, CM_MAP_FN_NAME);
                        mapfn = cosmos_lookup_cascade( cm, last, fnpath );


                }


                /* run lookup module */

                printf("cosmos_lookup deligate func %s\n", cur);



                if( last->parent == NULL )
                {
                        HIERR("cosmos_lookup: err: par->parent NULL");
                        return COSMOS_ID_NULL;
                }




                lookfn = last->parent->lookfn;

                if( lookfn == NULL )
                {
                        HIERR("cosmos_lookup: err: lookfn NULL");
                        return COSMOS_ID_NULL;
                }


                found = lookfn(cm, last, cur);



                if( found == NULL && cascades != NULL )
                        found = cosmos_lookup_cascade( cm, cascades, strstate );



                if( found == NULL )
                        return COSMOS_ID_NULL;



                /* keep this next assignment as a stub for when we add frame-relative lookup functions 

                found->lookfn = lookfn;
                */



                br = last->branch;
                btree_put(br, (bkey_t)key, (bval_t)found);

                last = found;
        }

        free(s);
        ptr_stack_cleanup(cascades);
        ptr_stack_cleanup(strstate);

        /* memory TODO:  free the strings in strstate */

        return (cosmos_id_t)found;
}





