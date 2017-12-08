


cosmos object
-------------

## strings ##
maps a hashval to a string


## pathstrings ##
maps a pathstring to an aframe id


## aframes ##
maps aframe id to an aframe


## dcels ##
maps a dcel id to a dcel



scanners and executables
------------------------

can be accessed via aframe id, dcel id, or pathstring.


## via a pathstring ##

    /.cosm/types/ox.so/yyparse

above is a pathstring to a function pointer.

    /.cosm/bin/ox-to-yaml

above is a pathstring to an executable.

    /.cosm/bin/such.sh/myfunc

above is a pathstring to a shell function.

pathstrings map to an access frame.


## via an access frame id ##

an access frame has a dcel.


## via a dcel id ##

a dcel can reference a function pointer or an external utility.

in the case of a scanner, we want to find the child of the .so called yyparse.  the dcel value is a function pointer.  typecast it and run it.


building the cosmos object
--------------------------

init a new cosmos object

    cosmos_new();

add and get items

    cosmos_string_put( cosmo, str );

    cosmos_string_get( cosmo, id );

    cosmos_path_put( cosmo, str );

    cosmos_path_get( cosmo, id );

    cosmos_aframe_put( cosmo, afr );

    cosmos_aframe_get( cosmo, id );

    cosmos_dcel_put( cosmos, dc );

    cosmos_dcel_get( cosmos, id );

