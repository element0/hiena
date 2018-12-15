



configuring cosmos
------------------

   cosmos_config.h
   cosmos.conf


cosmos configuration begins at the point of installation.

installation can be as simple as the download location.

    cd <location>; git <cosmos>
    cd cosmos; make in-place


the config

    <location>/cosmos/etc/cosmos.conf
    <location>/cosmos/lib/libcosmos.so
    <location>/cosmos/lib/cosmos/mod/file.so
    <location>/cosmos/lib/cosmos/mod/lookup.so



implementation

   COSMOS_INSTALL_ROOT=<location>/cosmos

   conf_relpath=/etc/cosmos.conf
   libcosmos_relpath=/lib/libcosmos.so
   filemod_relpath=/lib/cosmos/mod/file.so
   lookupmod_relpath=/lib/cosmos/mod/lookup.so


path search could be as simple as

   {COSMOS_INSTALL_ROOT,HOME,HOST_USR,HOST_USR_LOCAL,HOST_ROOT}{conf_relpath,libcosmos_relpath,filemod_relpath,lookupmod_relpath}
