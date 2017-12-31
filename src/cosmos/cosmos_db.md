


cosmos object
-------------

The cosmos db object has:

        - databases
        - handles to boot modules


## strings ##
maps a uint64_t hashval to a string

(access frames reference strings by hash value)

## pathstrings ##
maps a pathstring to an aframe id


## aframes ##
a tree structure of aframes.

aframes branches are keyed by string hash values (relative to te namespace of the aframe).

(the cosmos string db is kept for reverse lookups of a hashed value).

linked list destructor chain for end of life.

root access frame belongs to the db, not to the file system.  multiple fs roots can be children of the db root.

    cosmosdb
        aframe  // db root
            cosmos://skinner@badfish:cnrelease/ // these are context roots
            cosmos://skinner@badfish:httpd/
            cosmos://skinner@badfish:gnome/
                /home/skinner/deepwater         // this is a mountpoint
                    scuba.ox                    // these are branches
                    scuba.html                  // they can branch to same data
                    scuba/                      // presented differently


the string values of each aframe path segment can be concatenated into a global pathname.  the hash value of this pathname can be a key to a global access-frame-by-path db.

recap:  an access frame can be accessed by a path walk over the access frame tree or by a full pathname index.


## dcels ##
dcels kept in-memory

linked list destructor chain for cosmosdb end of life.







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

