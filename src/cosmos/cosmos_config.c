
#include "cosmos_config.h"
#include "../hierr.h"

int cosmos_config(struct cosmos *cm)
{
        if( cm == NULL )
        {
                HIERR("cosmos_config: cm NULL");
                return -1;
        }

        cm->modlibpath = CM_MODLIBPATH;

        return 0;

}