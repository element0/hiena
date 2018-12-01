
/* a demo to generate a function call from a template */

#include <stdio.h>
#include <stdint.h>




int64_t addfn(int64_t x, int64_t y)
{
        int64_t ret = x + y;

        printf("addfn %lu,%lu\n", x,y);

        return ret;
}


int multfn(int x, int y)
{
        return x * y;
}


void main()
{
   int64_t(*fn)(int64_t,int64_t) = addfn;
   int64_t x = 5;
   int64_t y = 3;
   int64_t res = 0;

   printf("main %lu,%lu\n",x,y);

   asm volatile (
        "movq %1, %%rdi \n\t"
        "movq %2, %%rsi \n\t"
        "call addfn \n\t"
        "movq %%rax, %0 \n\t"
        : "=g" (res)
        : "g" (x), "g" (y), "g" (*fn)
   );
   
   printf("res = %lu\n", res);

   res = addfn(x,y);
   printf("res = %lu\n", res);
}