#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>




struct double_int_t
{
        int i;
        int j;
};

void main()
{
    union
    {
        struct double_int_t d;
        void *p;
    }x;

    x.d.i = 7;
    x.d.j = 32;


    printf("sizeof(char) == %lu\n", sizeof(char));

    printf("sizeof(int) == %lu\n", sizeof(int));

    printf("sizeof(void *)==%lu\n", sizeof(void *));

    printf("sizeof(struct double_int_t) == %lu\n", sizeof(struct double_int_t));

    printf("x.p == %lu\n", x.p);

    printf("x.d.i == %d\n", x.d.i);

    printf("x.d.j == %d\n", x.d.j);

    printf("sizeof(struct dirent) == %lu\n", sizeof(struct dirent));

}