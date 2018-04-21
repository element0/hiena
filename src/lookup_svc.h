


#ifndef _HIENA_LOOKUP_SVC_H_
#define _HIENA_LOOKUP_SVC_H_


int lookup_set_target( struct lookup_hdl *h, struct hiena_dcel *dc );

struct hiena_dcel *lookup_find_child( struct lookup_hdl *h, char *dc );

struct hiena_dcel *lookup_find_prop( struct lookup_hdl *h, char *dc );

struct hiena_dcel *lookup_grind( struct lookup_hdl *h, char *dc );


#endif /* ! _HIENA_LOOKUP_SVC_H_ */
