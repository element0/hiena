#ifndef HIENA_FH_H
#define HIENA_FH_H

#include <stdlib.h>
#include "hiena_svc.h"

struct hiena_fh
{
        void *addr;
        struct hiena_svc *ops;

        void *fh;  //depr

        /** internal file handle */
        void *ifh; //use this

        off_t pos;
        int is_eof;
};


#endif /*!HIENA_FH_H*/
