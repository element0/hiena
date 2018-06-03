#ifndef _COSMOS_CONFIG_H_
#define _COSMOS_CONFIG_H_


#include "cosmos_db.h"


#define CM_MODLIBPATH ".cosm/lib/cosmos/modules"
#define CM_MODSUFFIX ".so"

#define CM_LOOKUP_FN_NAME "cosmos_lookup_fn"



int cosmos_config(struct cosmos *);



#endif  /*! _COSMOS_CONFIG_H_ */
