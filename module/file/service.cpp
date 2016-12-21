#include <fileops.hh>
#include <fcntl.h>
#include <cstdio>

using namespace std;


void *fileservice_open ( const char *filename, const char *mode )
{
	return fopen( filename, mode );
}

ssize_t fileservice_read ( void *ptr, size_t size, size_t nmemb, void *fh )
{
	return fread( ptr, size, nmemb, static_cast<FILE *>(fh) );
}

ssize_t fileservice_write ( const void *ptr, size_t size, size_t nmemb, void *fh )
{
	return fwrite( ptr, size, nmemb, static_cast<FILE *>(fh) );
}

int	fileservice_close ( void *fh )
{
	return fclose(static_cast<FILE *>(fh));
}

fileops *hiena_module_init() {
	fileops *fo = new fileops {
		fileservice_open,
		fileservice_read,
		fileservice_write,
		fileservice_close
	};
	return fo;
}
