#ifndef _COSMOS_BIND_H_
#define _COSMOS_BIND_H_

#include "cosmos_db.h"
#include "cosmos_id.h"



cosmos_id_t cosmos_bind( struct cosmos *cm, cosmos_id_t dest, char *protocol, char *addr, cosmos_id_t context);

cosmos_id_t cosmos_cascade_bind( struct cosmos *cm, cosmos_id_t af, cosmos_id_t af2 );

cosmos_id_t cosmos_bind_uri( struct cosmos *cm, cosmos_id_t targ, char *addr, cosmos_id_t context);



#endif /*! _COSMOS_BIND_H_ */
