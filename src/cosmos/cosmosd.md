



cosmosd
-------

the daemon of libcosmos.

runs 1 per user per host.

forked if needed by cosmos_init.

initializes root access frame for this daemon by running host-device scanner.

keeps the databases.

links to libcosmos.

keeps the vm socket addresses


databases
---------
aframe database
vm database
   socket addresses



cosmos rpc api
--------------
provided internally by cosmosd. used by clients via cosmosmsg rcp.




cosmosd client api
------------------
provided by libcosmos. used by client process. wraps a cosmomsg rpc.


  aframe *cosmosd_get_access_frame( axid );

  aframe *cosmosd_lookup( axid, str );



cosmosd code structure
----------------------

cosmosd.c
cosmos_vm_core.c


