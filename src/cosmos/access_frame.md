


access_frame 
------------

aka( context_frame )


the cosmos sets this up as

    dcel_t *cosm;
    dcel_t *dcel;
    dcel_t *env;


access_path
-----------

extends access frame with links to a parent frame and a lookup_cache to child access frames.  (besides the root access frame, every access frame is a product of a lookup.)

    access_frame_t *parent;
    btree_t *lookup_cache;

The access path properties can be declared within the access_frame structure, since one is not without the other.


prop: env
---------
dcel type with a buffer backing.

envars are accessed via these dcel functions:

  r = dcel_child( dcel, varname );
  val = dcel_read( r, &len );

a dcel convenience macro for above:

  val = dcel_child_val( dcel, varname, &len );


an access_frame method:

  val = aframe_envar( aframe, varname, &len );

above could be implemented thus:

  dcel = aframe_env( aframe );
  r = dcel_child( dcel, varname );
  val = dcel_read( r, &len );

