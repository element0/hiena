#include <stdarg.h>
#include <stdint.h>
#include "../hierr.h"


/* virtual function wrappers,
   go into a dylib with static support functions */



const int vfncount = 1;
const int bankno = 1;

intptr_t vfn0001(int init, ...)
{
    static int ini = -1;
    int i;
    va_list ap;

    /* vars for demo only */
    /* function morphs into a calc */
    int res = 0;
    int cur = 0;
    /*--------*/

        
    if(ini == -1)
    {
        if(init < 0)
        {
            HIERR("vfn0001: err: can't init: ini -1 AND init < 0");
            return NULL;
        }
        ini = init;

        printf("initialized: ini %d\n", ini);

        return vfn0001;
    }

    printf("ini %d\n", ini);

    if(ini > 0)
    {
        /* demo morphism: calc */

        /* include first arg */
        res += init;
        
        va_start(ap, init);
        for(i = 0; i < (ini-1); i++)
        {
            cur = va_arg(ap, int);
            res += cur;
        }
        va_end(ap);

        // printf("result: %d\n", res);

        return res;
    }
    

    return NULL;
}

