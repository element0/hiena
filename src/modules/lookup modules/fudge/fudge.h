

#ifndef _HIENA_FUDGE_H_
#define _HIENA_FUDGE_H_

typedef void* yyscan_t;

#include "../../../lookup_hdl.h"
#include "../../../dcel.h"
#include "../../../access_frame.h"
#include "../../../cosmos.h"

int fudge_parse(struct lookup_hdl *);

char *fudge_expand(struct lookup_hdl *, char *);

struct access_frame *cosmos_lookup_fn(struct cosmos *, struct access_frame *, char *);


#endif  /* ! _HIENA_FUDGE_H_ */
