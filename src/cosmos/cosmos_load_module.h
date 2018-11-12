#ifndef COSMOS_LOAD_MODULE
#define COSMOS_LOAD_MODULE

#include "cosmos_db.h"


/**
2018-10-10 renamed load_mod() cosmos_load_mod()
*/



/** load any type of module for 
   cosmos from a pathname;
   store module in a dcel.

   module is accessed by pathname
   or hash id.  pathname is hashed
   to id.  id retrieves module. 

   @param cm   the cosmos db -- do we need this?  TBD
   @param par  the access frame gto save the module in
   @param fpath  the module file relative to PWD of process
  */


struct cosmos_module *cosmos_load_mod( struct cosmos *cm, char *fpath );



#endif /* !COSMOS_LOAD_MODULE */
