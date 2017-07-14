#include "hiena_svc.h"
#include <sys/stat.h>

off_t get_filesize( char *n )
{
        struct stat sb;
        stat( n, &sb );
        return sb.st_size;
}