#ifndef _COSMOS_LIMITS_H_
#define _COSMOS_LIMITS_H_

#include <limits.h>
#include <unistd.h>


/* FIXME: please improve procedure for setting PATH_MAX. I don't think sizeof(uintptr_t) is relevant. */


#ifndef PATH_MAX
  #ifndef _POSIX_PATH_MAX
    #define PATH_MAX sizeof(uintptr_t)
  #else
    #define PATH_MAX _POSIX_PATH_MAX
  #endif
#endif
  


#endif /*! _COSMOS_LIMITS_H_ */
