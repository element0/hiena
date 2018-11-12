#ifndef _COSMOS_CONFIG_H_
#define _COSMOS_CONFIG_H_


/**********************************/
 /* OS relative names */

#define COSMOS_DISTRO_NAME "cosmos"

#define COSMOS_METADIR_NAME ".cosm"

#define COSMOS_ETCDIR_NAME "etc"

#define COSMOS_LIBDIR_NAME "lib"

#define COSMOS_MODULEDIR_NAME "module"

#define COSMOS_VMDIR_NAME "vm"

#define COSMOS_MOD_SUFFIX ".so"


/**********************************/
 /* metadirectory relative paths */

#define COSMOS_ETCDIR_RELPATH COSMOS_METADIR_NAME "/" COSMOS_ETCDIR_NAME "/" COSMOS_DISTRO_NAME


#define COSMOS_LIBDIR_RELPATH COSMOS_METADIR_NAME "/" COSMOS_LIBDIR_NAME "/" COSMOS_DISTRO_NAME


#define COSMOS_MODULEDIR_RELPATH COSMOS_LIBDIR_RELPATH "/" COSMOS_MODULEDIR_NAME



/**********************************/
     /* default module names */

#define COSMOS_LOOKUPMOD_NAME "lookup"

#define COSMOS_HOST_SVCMOD_NAME "file"



/**********************************/
 /* default install locations */

#define COSMOS_HOST_ROOTDIR_NAME "/"

#define COSMOS_HOST_ETCDIR_PATH COSMOS_HOST_ROOTDIR_NAME "/" COSMOS_ETCDIR_NAME "/" COSMOS_DISTRO_NAME

#define COSMOS_HOST_LIBDIR_PATH COSMOS_HOST_ROOTDIR_NAME "/" COSMOS_LIBDIR_NAME "/" COSMOS_DISTRO_NAME

#define COSMOS_HOST_MODDIR_PATH COSMOS_HOST_LIBDIR_PATH "/" COSMOS_MODULEDIR_NAME


#define COSMOS_HOST_LOOKUPMOD_FPATH COSMOS_HOST_MODDIR_PATH "/" COSMOS_LOOKUPMOD_NAME COSMOS_MODSUFFIX ".so"

#define COSMOS_HOST_SVCMOD_FPATH COSMOS_HOST_MODDIR_PATH "/" COSMOS_HOST_SVCMOD_NAME COSMOS_MODSUFFIX ".so"


 /* PATH style search locations
    These are used at program startup to locate the cosmos installation.
  */

#define COSMOS_CONFIG_PATHVAR COSMOS_ETCDIR_RELPATH ":~/" COSMOS_ETCDIR_RELPATH ":" COSMOS_HOST_ROOTDIR_NAME "/" COSMOS_ETCDIR_RELPATH ":" COSMOS_HOST_ETCDIR_PATH


#define COSMOS_LIB_PATHVAR COSMOS_LIBDIR_RELPATH ":~/" COSMOS_LIBDIR_RELPATH ":" COSMOS_HOST_ROOTDIR_NAME "/" COSMOS_LIBDIR_RELPATH ":" COSMOS_HOST_LIBDIR_PATH



/*
    EG: cosmos vm's are under {COSMOS_LIB_PATHVAR}/COSMOS_VMDIR_NAME
*/



/**********************************/



#define COSMOS_LOOKUP_FN_NAME "cosmos_lookup_fn"

#define COSMOS_MAP_FN_NAME "cosmos_map_fn"



#endif  /*! _COSMOS_CONFIG_H_ */
