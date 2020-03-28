#ifndef _COSMOS_SERVICE_FUNCTIONS_H_
#define _COSMOS_SERVICE_FUNCTIONS_H_



struct cosmos_service_func_block {
    void *(*fopen)(const char *url, const char *operation);
    int (*fclose)(void *file);
    int (*feof)(void *file);
    size_t (*fread)(void *ptr, size_t size, size_t nmemb, void *file);
    char *(*fgets)(char *ptr, size_t size, void *file);
    void (*rewind)(void *file);
};

#endif /*! _COSMOS_SERVICE_FUNCTIONS_H_ */