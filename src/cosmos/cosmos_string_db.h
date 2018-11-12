#ifndef _COSMOS_STRING_DB_H_
#define _COSMOS_STRING_DB_H_

#include <stdint.h>


struct cosmos;
typedef uint64_t cosmos_strid_t;
#define COSMOS_STRID_NULL 0

/** 
 * this copies the input string and stores a pointer to the copy.  the caller is responsible for freeing the original.
 */
cosmos_strid_t cosmos_put_string(struct cosmos *, char *);


/**
 * this returns a copy of the string identified by string id.  the caller is responsible for freeing the copy. 
 */
char *cosmos_get_string(struct cosmos *, cosmos_strid_t );


cosmos_strid_t cosmos_string_id( char * );


int cosmos_string_release( struct cosmos *, cosmos_strid_t, char * );


#endif /* !_COSMOS_STRING_DB_H_ */
