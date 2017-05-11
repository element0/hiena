#ifndef HIENA_FH_H
#define HIENA_FH_H

#include <stdlib.h>
#include "hiena_svc.h"

struct hiena_fh
{
        struct hiena_svc *ops;
        void *addr;
        void *fh;
        off_t pos;
        int is_eof;
};

//---- deprec. ----
struct hiena_fh *hiena_fh_new();
int hiena_fh_cleanup( struct hiena_fh * );


#endif /*!HIENA_FH_H*/
