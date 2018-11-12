/* file_module.c */

#include "../../cosmos/cosmos_module.h"

struct cosmos_module cosmos_module;

struct cosmos_module_ops cosmos_module_ops;

/* moved file source function into production function codespace */


struct cosmos_module_ops cosmos_module_ops = {
        .source = NULL;
};


struct cosmos_module cosmos_module = {
        .svc = file_svc_ops,
};
