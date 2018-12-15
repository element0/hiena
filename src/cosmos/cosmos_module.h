#ifndef _COSMOS_MODULE_H_
#define _COSMOS_MODULE_H_


#include "../hiena_svc.h"
#include "cosmos_id.h"
#include "cosmos_db.h"


typedef struct cosmos_module cosmos_module_t;


struct cosmos_module
{
        void *dl;

        cosmos_id_t (*lookup)( struct cosmos *, cosmos_id_t par, char *rqstr );

        struct hiena_svc *svc;
};



#endif  /*! _COSMOS_MODULE_H_ */