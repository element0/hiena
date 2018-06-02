#ifndef HIENA_PRODUCER_FUNCS_H
#define HIENA_PRODUCER_FUNCS_H

#include "cosmos.h"


cosmos_id_t prod_src(char *modname, char *addr, struct cosmos *);

cosmos_id_t prod_map(cosmos_id_t, char *, struct cosmos *);

cosmos_id_t prod_find_child(cosmos_id_t, char *, struct cosmos *);

cosmos_id_t prod_find_prop(cosmos_id_t, char *, struct cosmos *);

cosmos_id_t prod_transform(cosmos_id_t, char *, struct cosmos *);



/* chopping block... */

struct hiena_dcel *prod_exec( struct prod_sequence * );


#endif /*! HIENA_PRODUCER_FUNCS_H */
