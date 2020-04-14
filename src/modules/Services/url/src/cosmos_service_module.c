// 2020-03-30 rh
// cosmos_service_module

/* direct inclusion */
#include "curl_fopen.c"


/* re-map included functions */
#include "cosmos/cosmos_service_func_block.h"


struct cosmos_service_func_block  cosmos_service_ops = {
    .fopen = (void *(*)(const char *, const char *))url_fopen,
    .fclose = (int (*)(void *))url_fclose,
    .feof = (int (*)(void *))url_feof,
    .fread = (size_t (*)(void *, size_t, size_t, void *))url_fread,
    .fgets = (char *(*)(char *ptr, size_t size, void *))url_fgets,
    .rewind = (void (*)(void *))url_rewind,
    .fseeko = (int (*)(void *, off_t, int))url_fseeko,
};

  
   
   
   
   
   
