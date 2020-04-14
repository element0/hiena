#ifndef _COSMOS_SERVICE_FUNCTIONS_H_
#define _COSMOS_SERVICE_FUNCTIONS_H_



struct cosmos_service_func_block {
    void *(*fopen)(const char *, const char *);
    int (*fclose)(void *);
    int (*feof)(void *);
    size_t (*fread)(void *ptr, size_t size, size_t nmemb, void *file);
    char *(*fgets)(char *, size_t, void *);
    char *(*fgetc)(void *);
    void (*rewind)(void *);
    int (*fseeko)(void *stream, off_t offset, int whence);
};

#endif /*! _COSMOS_SERVICE_FUNCTIONS_H_ */