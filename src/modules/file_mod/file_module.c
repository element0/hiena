/* file_module.c */

#include "../../cosmos/cosmos_module.h"

struct cosmos_module cosmos_module;

struct cosmos_module cosmos_module = {
        .source = cosmos_source_fn,
};


