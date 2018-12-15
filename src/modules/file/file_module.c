/* file_module.c */

#include "../../cosmos/cosmos_module.h"
#include "file_svc.h"


/* moved file "source" function into production function codespace */


struct cosmos_module cosmos_module = {
        .svc = &file_svc_ops,
};
