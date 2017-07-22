
#ifndef _HIENA_SCANNER_LIB_H_
#define _HIENA_SCANNER_LIB_H_


/* based on hesei 27 */


#include "scanner.h"
#include "btrees.h"


struct hiena_slib {
    struct hiena_scanner *newest;
    void *global_token_table;
    void *global_scanner_table;

        btree_t *db;
};


struct hiena_slib *slib_load_dir( char *dirpath, struct hiena_slib *optional );

void slib_cleanup( struct hiena_slib * );

struct hiena_scanner *get_scanner(char *, struct hiena_slib *);



/* key comparison op */
int slib_key_lt(void *k, void *k2);


struct hiena_scanner *slib_get_next_scanner(struct hiena_slib *, struct hiena_scanner *);



int slib_rm_scanner( struct hiena_slib *, struct hiena_scanner *);



#endif /*!_HIENA_SCANNER_LIB_H_*/
