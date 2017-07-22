#ifndef HIENA_SCANNER_H
#define HIENA_SCANNER_H

#include "scanner_svc.h"


struct hiena_scanner {
   
    /* GENERAL */
    char          *name;
    void          *dl;


    /* COMPILER VERSION 1
       and newer */

    int compiler_version;


    /* COMPILER VERSION 1 */
    int    name_str_dim;
    char **name_str;
    int   *name_table;
    int   *fsm_table;


    /* COMPILER VERSION 0 */
    struct scanner_svc_ops *op;
    struct hiena_scanner *prev;
    struct hiena_scanner *next;

    /* reminder: flexible array
       members must be at end of
       struct */

    char	  *allowed_child_scanners[];

};

typedef struct hiena_scanner scannerserver;

scannerserver *hiena_scanner_create();

#endif /*! HIENA_SCANNER_H */
