#ifndef COSMOS_FILE_SYSTEM_H
#define COSMOS_FILE_SYSTEM_H

#include <dirent.h>
#include <sys/stat.h>


int snafu_stat(cosmos_id_t, struct stat *);

cosmos_id_t cosmos_lookup(cosmos_id_t, char *);

struct dirent *cosmos_readdir( cosmos_dirh_t );

cosmos_fh_t cosmos_open( cosmos_id_t );

size_t cosmos_read(void *, size_t, size_t, cosmos_fh_t);



#endif /* !COSMOS_FILE_SYSTEM_H */