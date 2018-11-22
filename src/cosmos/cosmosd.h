#ifndef COSMOS_DAEMON_H
#define COSMOS_DAEMON_H

#include "cosmosdb.h"
#include "cosmos_server_core.h"


struct cosmos_daemon {
	struct cosmos *cosmos;
	struct cosmos_server_core *server_core;
};


#endif /* !COSMOS_DAEMON_H */
