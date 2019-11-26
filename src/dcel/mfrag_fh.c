#include "mfrag_fh.h"


struct mfrag_fh *mfrag_fh_new()
{
        struct mfrag_fh *mfh;
        
        mfh = malloc(sizeof(*mfh));

        return mfh;
}

int mfrag_fh_cleanup( struct mfrag_fh *mfh )
{
        if( mfh == NULL )
                return -1;

        free( mfh );

        return 0;
}