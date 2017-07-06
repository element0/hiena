#ifndef _HIENA_DCEL_H_
#define _HIENA_DCEL_H_



#include "frag.h"


#define dcel_retain( dc ) dc->retain++

#define dcel_release( dc ) dc->retain--


struct hiena_dcel {
        struct hiena_frag *frag;
        int retain;
};

#endif /*! _HIENA_DCEL_H_ */