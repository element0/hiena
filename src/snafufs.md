

snafufs
-------




create user-host-context root
-----------------------------

a context is a configuration which imposes constraints on access to a dcel, such as two different desktop environments running on the same host, under the same user, each is a different context.

a context access frame can share the same root dcel as another context, but the local .cosm will differ.

  cosmos_db
    root
      "skinner@badfish"
        context-"demo"
          "/"
            .cosm
              <demo config>
        context-"fishbowl"
          "/"
            .cosm
              <fishbowl config>

a generic default context exists

  cosmosdb
    aframe
      skinner@badfish
        "/"

each time smafu_init is called, create a user-host-context aframe if needed.

  url: cosmos://user@host/context/

  cosmosdb
    aframe
      user@host
        context

using these calls:

  cosmos_mknod( aframe, null_prodinstr, userhost_str, mode, dev );

  cosmos_mknod( userhost_aframe, null_prodinstr, context_str, mode, dev );




create volume dcel
------------------

each time snafufs is run, create a mountpoint aframe:

  url: cosmos://user@host/context/mountpoint
  url: cosmos://user@host/context/home/user/example_mnt

  cosmosdb
    aframe
      user@host
        context
          home
            user
              example_mnt


and create a prod instr.  fn_aframe is derived from context_aframe.

  prod instr
    context_aframe: &(aframe/user@host/context/home/user/)
    fn_aframe: &((context_aframe)/.cosm/svc/file/source)
    fn: &((fn_aframe)/dcel:value)
    argc: 1
    argv: { mountfpath }


run to create dcel and store dcel at example_mnt







ino's
-----

snafufs ino values are pointers to in-memory access frames.

this is opaque to snafufs as the ino's are passed through to cosmos_fs functions.

access frames are memory managed by the cosmosdb.


mounting a directory ontop of itself
------------------------------------

snafufs -> cosmos -> stdio -> 

snafufs makes calls to cosmos.  cosmos makes calls to service modules.
service modules make calls into the os.

a separate passthrough filesystem could be used to lock a directory handle in an open position.
this passthrough file system would be mounted outside the snafufs mount and be bound via cosmos to the snafufs root.

ie, an example procedure:


the user runs

    snafufs /home/user/target

snafufs calls cosmos to create an access frame path for the volume root:  /home/user/target

snafufs forks a passthrough fs which opens a DIR handle on /home/user/target and mounts it at /run/snafufs/hashid

snafufs calls cosmos_source() and binds file:///run/snafufs/hashid to the cosmos db access frame: /home/user/target

snafufs mounts the access frame over the mountpoint /home/user/target using the non-empty mount option.

now, essentially, the system acts as a passthrough file system.  but it's all done via cosmos services.  and additional "productions" can be bound into the access frame to create a grid volume.

when snafufs is unmounted, it unmounts the passthroughfs which releases the DIR.


