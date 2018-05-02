#ifndef _COSMOS_STRING_DB_H_
#define _COSMOS_STRING_DB_H_

#include <sys/types.h>

struct cosmos;
typedef uint64_t cosmos_strid_t;
#define COSMOS_STRID_NULL 0


cosmos_strid_t cosmos_put_string(struct cosmos *, char *);

char *cosmos_get_string(struct cosmos *, cosmos_strid_t );

cosmos_strid_t cosmos_string_id( char * );

int cosmos_string_release( struct cosmos *, cosmos_strid_t, char * );


#endif /* !_COSMOS_STRING_DB_H_ */
