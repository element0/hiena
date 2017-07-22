

#ifndef HIENA_SCANNER_LIB_ENTRY_H
#define HIENA_SCANNER_LIB_ENTRY_H

#include "scanner.h"
#include "slib.h"


struct hiena_slib_entry {
    struct hiena_scanner *ss;
    struct hiena_scanner *prev;
    struct hiena_scanner *next;
    struct hiena_slib *slib;
};


#endif /*! HIENA_SCANNER_LIB_ENTRY_H */