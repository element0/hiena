#ifndef COSMOS_INIT_H
#define COSMOS_INIT_H

#include "cosmos_db.h"

/**
 * Global cosmos object.
 */
struct cosmos cosmos;

struct cosmos *cosmos_init( int, char ** );

#endif /* !COSMOS_INIT_H */