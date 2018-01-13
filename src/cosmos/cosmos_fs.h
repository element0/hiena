#ifndef COSMOS_FILE_SYSTEM_H
#define COSMOS_FILE_SYSTEM_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cosmos_db.h"


typedef void * cosmos_dirh_t;
typedef void * cosmos_fh_t;



int cosmos_stat(struct cosmos *, cosmos_id_t, struct stat *);

cosmos_id_t cosmos_lookup(struct cosmos *, cosmos_id_t, char *);

struct dirent *cosmos_readdir( cosmos_dirh_t );

cosmos_fh_t cosmos_open(struct cosmos *, cosmos_id_t );

size_t cosmos_read(void *, size_t, size_t, cosmos_fh_t);

cosmos_id_t cosmos_ln(struct cosmos *, cosmos_id_t, cosmos_id_t);

cosmos_id_t cosmos_mknod(struct cosmos *, cosmos_id_t, char *, mode_t, dev_t);

cosmos_id_t cosmos_mknod_path(struct cosmos *, cosmos_id_t, char *, mode_t, dev_t);

cosmos_id_t cosmos_mkdir(struct cosmos *, cosmos_id_t, char *, mode_t);

#endif /* !COSMOS_FILE_SYSTEM_H */
