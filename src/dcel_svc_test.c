#include "dcel_svc.h"






int main()
{
        struct hiena_svc *ops;
        void *dfh;
        int c;

        ops = &dcel_svc_ops;

        dfh = ops->open( NULL, "r" );
        c = ops->getchar( dfh );
        ops->close( dfh );

        return 0;
}