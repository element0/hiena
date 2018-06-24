#ifndef _COSMOS_CONFIG_H_
#define _COSMOS_CONFIG_H_


#include "cosmos_db.h"


#define CM_METADIR_NAME ".cosm"

#define CM_COSMOSLIBPATH "/lib/cosmos"

#define CM_MODLIBPATH CM_METADIR_NAME CM_COSMOSLIBPATH "/modules"

#define CM_INITMODLIBPATH CM_METADIR_NAME CM_COSMOSLIBPATH "/init/modules"

#define CM_MODSUFFIX ".so"

#define CM_SOURCE_MODULE_NAME "file"

#define CM_LOOKUP_MODULE_NAME "lookup"

#define CM_LOOKUP_FN_NAME "cosmos_lookup_fn"

#define CM_MAP_FN_NAME "cosmos_map_fn"


char *cm_mod_symbols[]={
    "open",
    "close",
};



int cosmos_config(struct cosmos *);



#endif  /*! _COSMOS_CONFIG_H_ */
