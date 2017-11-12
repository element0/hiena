



cosmosd
-------

the daemon of libcosmos.

runs 1 per user per host.

forked if needed by cosmos_init.

initializes root access frame for this daemon by running host-device scanner.

keeps the databases.

links to libcosmos.


databases
---------
source database
xformr database
scannr database

the database entries could be stored by checksum of their element.



cosmosd api
-----------

  aframe *cosmosd_get_access_frame( axid );

  aframe *cosmosd_lookup( axid, str );



