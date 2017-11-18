
API layers in detail
--------------------

this document lists the API objects and functions of each layer (layers were introduced in "architecture.md").

each section describes the API which a particular layer USES, rather than provides.

i want to create a mental stack-trace through the layers so as to define each API.


description
-----------

snafufs invokes libcosmos.  libcosmos daemonizes and initializes a root access path for the user on the host.

the snafufs requests an ino for a url (local file or remote protocol) of the mountpoint.  it uses the libcosmos client interface.

libcosmos client turns the request into a serial request over a socket to the cosmosd.

the cosmosd parses each request and calls an appropriate cosmosd file system function.    

ie.

   cosmosd_lookup( cosmosd, ino, str );

The cosmosd function gets an access frame from the access_frame_db keyed by ino.

   aframe_db_get( cosmos, ino );

the cosmosd function gets the lookup module:

   lookupfunc =
   aframe_get_lookupfunc( cosmos, aframe );

the the cosmosd function calls lookup:

   lookupfunc( cosmos, aframe, str );

the lookupfunc reads the aframe to get the cosm id;  it queries the cosmos db for the cosm object; from that, it gets the production functions which it executes to resolve the lookup.  it returns an aframe.

the cosmosd func mulls over the new aframe and saves it and its components into appropriate databases.  it returns the ino key over the socket using a return message.


snafufs
-------

fuse api (described in fuse docs)


libcosmos api

  cosmos_init();

  ino = cosmos_get_ino( url );
  stbuf = cosmos_stat( ino );
  fuse_reply_entry = lookup( ino, str );
  fh = cosmos_fopen( ino );
  cosmos_read( fh, buf, len, off );


libcosmos
---------

cosmosd server via domain socket.

messages

  getino "url"\n
  stat ino\n
  lookup ino "str"\n
  fopen ino\n
  read fh len off\n
  

<socket>
--------

cosmosd
-------

uses libcosmos for init

  aframe = cosmos_aframe_init();
  cosm = cosmos_cosm_init( fpath );
  cosmos_slib_load_dir( fpath );
  cosmos_xflib_load_dir( fpath );
  cosmos_lookup_load( fpath );

reads messages from socket.

uses lookupmod
  
  aframe = lookupmod->lookup( aframe, str );


lookupmod
---------

  argv = fudge_expand_alias( aframe, str, &argc );

  prodcr = aframe_get_scannr( aframe, argv[0]);

  prodcr = aframe_get_xformr( aframe, argv[0]);

  prodcr = aframe_get_sourcr( aframe, argv[0]);

  prodexec( aframe, prodcr, argc, argv );


prodexec
--------

this will be the place to put the grid code.

scannr so

  dcel_fh.h
  dcel_mapsvc.h
  frag_curs.h
  scanner_hdl.h

xformr so

sourcr so


external tool
-------------

libcosmos
libhiena
cosmos tools
hiena tools

  fh = cosmos-open url
  tok = cosmos-gettok fh want_tok
  tok = cosmos-findtok fh want_tok
  