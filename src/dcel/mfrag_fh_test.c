







#include "mfrag_fh.h"

int main()
{
        struct mfrag_fh *fh;

        fh = mfrag_fh_new();
        mfrag_fh_cleanup( fh );
        
        return 0;
}