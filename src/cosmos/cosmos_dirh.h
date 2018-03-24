#ifndef COSMOS_DIRH_H
#define COSMOS_DIRH_H

#include "cosmos_db.h"
#include "../access_frame.h"
#include "../btree_cpp.h"


struct cosmos_dirent {
        cosmos_id_t ino;
        char *d_name;
};


struct cosmos_dirh {
        struct cosmos *cosmos;
        struct access_frame *aframe;
        btree_curs *curs;
};


struct cosmos_dirh * cosmos_opendir(struct cosmos *, cosmos_id_t);

int cosmos_closedir( struct cosmos_dirh *);

struct cosmos_dirent *cosmos_readdir( struct cosmos_dirh * );



#endif /* !COSMOS_DIRH_H */
