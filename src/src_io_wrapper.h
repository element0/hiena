




#ifndef HIENA_SRC_IO_WRAPPER_H
#define HIENA_SRC_IO_WRAPPER_H

#include <stdio.h>
#include "mfrag.h"

struct hiena_src_io
{
        void *fh;
        size_t (*fread)( void *buf, size_t size, size_t numitems, void *fh );
};

size_t src_io_fread( void *dst, size_t size, size_t numitems, struct hiena_src_io *sio );


#endif /*!HIENA_SRC_IO_WRAPPER_H*/