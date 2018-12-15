#ifndef COSMOS_DLFCN_H
#define COSMOS_DLFCN_H

#include <stdint.h>


#define COSMOS_RTLD_LAZY 1
#define COSMOS_RTLD_NOW 2
#define COSMOS_RTLD_GLOBAL 256
#define COSMOS_RTLD_LOCAL 0
#define COSMOS_RTLD_NOVM 512


struct cosmos_dl_hdl {
        struct cosmos *cosmosdb;
        struct access_frame *aframe;
        uintptr_t dl;
        uintptr_t vmid;
};



void *cosmos_dlopen(struct cosmos *, struct access_frame *, const char *, int);

int cosmos_dlclose(void *);

void *cosmos_dlsym(void *, char *);


#endif    /* ! COSMOS_DLFCN_H */