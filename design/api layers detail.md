
API layers in detail
--------------------

this document lists the API objects and functions of each layer (layers were introduced in "architecture.md").

each section describes the API which a particular layer USES, rather than provides.

it is my intent to facilitate a mental stack trace through the layers and so define each API.


fs_snafu uses
-------------

fuse api (described in fuse docs)

cosmos api


cosmos_sys_svc {

  ino = get_ino( url )
  stat( ino )
  root_cosm = get_cosm( mntpoint )
  
}
