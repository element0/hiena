#ifndef COSMOS_DIRH_H
#define COSMOS_DIRH_H


struct cosmos_dirh {
        struct cosmos *cosmos;
        struct access_frame *aframe;
        btree_curs curs;
};


cosmos_dirh_t cosmos_opendir(struct cosmos *, cosmos_id_t);

int cosmos_closedir( cosmos_dirh_t );

struct dirent *cosmos_readdir( cosmos_dirh_t );



#endif /* !COSMOS_DIRH_H */
