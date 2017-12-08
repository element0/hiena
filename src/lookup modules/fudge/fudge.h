

#ifndef _HIENA_FUDGE_H_
#define _HIENA_FUDGE_H_

typedef void* yyscan_t;

#include "../../lookup_hdl.h"
#include "../../dcel.h"

int fudge_parse(struct lookup_hdl *);

char *fudge_expand(struct lookup_hdl *, char *);


#endif  /* ! _HIENA_FUDGE_H_ */