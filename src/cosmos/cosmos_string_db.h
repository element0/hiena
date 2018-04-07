#ifndef _COSMOS_STRING_DB_H_
#define _COSMOS_STRING_DB_H_

#include "cosmos_id.h"

struct cosmos;


cosmos_id_t cosmos_put_string(struct cosmos *, char *);

char *cosmos_get_string(struct cosmos *, cosmos_id_t );

cosmos_id_t cosmos_string_id( char * );

int cosmos_string_release( struct cosmos *, cosmos_id_t, char * );


#endif /* !_COSMOS_STRING_DB_H_ */
