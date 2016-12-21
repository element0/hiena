#ifndef _HIENA_FILEOPS_HH_
#define _HIENA_FILEOPS_HH_

#include <sys/types.h>


struct fileops {
	void *	(*open)	(const char *path, const char *mode);
	ssize_t	(*read)	(void *ptr, size_t size, size_t nmemb, void *fh);
	ssize_t	(*write)(const void *ptr, size_t size, size_t nmemb, void *fh);
	int 	(*close)(void *);
};

#endif /*_HIENA_FILEOPS_HH_*/
