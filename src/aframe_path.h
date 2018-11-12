#ifndef HIENA_AFRAME_VPATH_H
#define HIENA_AFRAME_VPATH_H


#include "cosmos.h"
#include "access_frame.h"


/* access frame paths */


struct access_frame *aframe_mkpath(struct cosmos *, struct access_frame *, char *);


#define aframe_mkflatpath(c,a,s) aframe_set_branch(a, cosmos_put_string(c,s),aframe_new())



#define aframe_by_path_id(a,id) aframe_get_branch(a,id)




#endif /* ! HIENA_AFRAME_VPATH_H */