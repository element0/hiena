#include <stdio.h>
#include <dlfcn.h>




int main(int argc, char *argv[])
{
    void *dl, *dl2;
    void *fn, *fn2;
    void *(*fninit)(int);
    void *(*fncall)();
    int (*addfn)(int, ...);
    int res;
    

    dl = dlopen("./vfnbank.so", RTLD_NOW);

    if(dl == NULL)
    {
        perror("dl NULL");
        return -1;
    }

    fn = dlsym(dl, "vfn0001");
    if(fn == NULL)
    {
        perror("fn NULL");
        dlclose(dl);
        return -1;
    }

    printf("dl = %u\nfn = %u\n",dl,fn);

    dl2 = dlopen("./vfnbank2.so", RTLD_NOW);

    if(dl2 == NULL)
    {
        perror("dl2 NULL");
        return -1;
    }

    fn2 = dlsym(dl2, "vfn0001");
    if(fn2 == NULL)
    {
        perror("fn2 NULL");
        dlclose(dl2);
        return -1;
    }

    printf("dl2 = %u\nfn2 = %u\n",dl2,fn2);


    fninit = fn;
    fninit(2);

    fncall = fn;
    fncall();

    addfn = fn;
    res = addfn(1,2);

    printf("addfn returned: %d\n",res);


    dlclose(dl2);
    dlclose(dl);
    return 0;
}