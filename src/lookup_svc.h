


#ifndef _HIENA_LOOKUP_SVC_H_
#define _HIENA_LOOKUP_SVC_H_


/* lookup_svc.h is a one-stop shop
   for lookup modules to include.
   Please #include anything they
   need here. */


#include "lookup_hdl.h"

#define YY_INPUT(buf,result,max_size) \
    { \
    static int pos = 0; \
    int c = yyextra->str[pos++]; \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }


int lookup_set_target( struct lookup_hdl *h, lookup_target_t * );

lookup_target_t *lookup_find_child( struct lookup_hdl *, char * );

lookup_target_t *lookup_find_prop( struct lookup_hdl *, char * );

lookup_target_t *lookup_transform( struct lookup_hdl *, char * );


#endif /* ! _HIENA_LOOKUP_SVC_H_ */
