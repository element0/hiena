




mapcel
======

- mapcel relation to frag


2017-10-16 1345

mapcel children
---------------

a mapcel has a flat list of direct descendents.


## flat directory vs. btree ##

how is the child list accessed?

a user may request an area described by the mapcel-fragment combo via a ruleid index.  this enables random nonlinear access to areas described by children.  however the index lives inside the dcel structure.

a parser will be more interested in sequential access.  likewise an index creation operation must scan every child cell so gains no speed from a random access model.

use flat list model as a natural intermediate structure between parsing and indexing. (2017-10-16)



2017-10-05 0700

a mapcel is relative to a frag
------------------------------

mapcels access can be random or sequential.

random access cells are accessed via directories and indexes.  sequential cells are accessed in series by a scanner module.

if all mapcels refer back to a frag they will be available for random access.  this will take up space in cells which are sequential only in nature.  an optimization may be warranted.

can we keep the fragment info in those links to mapcels?  how is an index acquired?


acquiring a mapcel from an index
--------------------------------

a dcel has a root frag and root mapcel.  this associates the root mapcel with a frag.  the root mapcel may contain one or more indexes.  an index could contain frag information.  we could require each mapcel to be relative to the index's frag.

we could alternatively create index item objects which save the {frag,offset} pair for each mapcel.  but if multiple indexes exist, thereby multiplying the item objects?


## eg. scanner maps to an index ##

given dcel D, root frag F0 and two sub-frags F1 F2.

scanner finds three mapcels Mc1 Mc2 Mc3 which span both frags via root F0.

Mc1 could assoc with F1.  Mc3 could assoc with F2.  Mc2 assoc with F0.

All three frags are mapped to cell Mc0 and indexed as a directory.

A simple array index cannot hold add'l data for the frags.  A complex index could contain a mirror frag structure:

index root
   frag related index 1
      mapcel ptr
      mapcel ptr
      mapcel ptr
   frag related index 2
      mapcel ptr
      mapcel ptr
   frag related index 3
      mapcel ptr
      mapcel ptr

All mapcel ptrs under a frag related index shall be mapped to that fragment.

The structure would look something like this:

    index_t {
        array_t *frag_ind;
    };

    frag_ind_t {
        frag_t *frag;
        array_t *arr;
    };

    array_t {
        int dim;
        element_t **elem;
    };


## memory footprint ##

in the above scenario each mapcel requires size_t, 8 bytes, for an offset in the reference frag.

the index tree requires 8 bytes for a pointer to a btree.

btree requires ?? bytes.

frag_ind_t  16 bytes

array_t  8 bytes per mapcel ptr
         4 bytes header

mapcel   8 bytes offset


compare:
4 mapcels vs 1 mapcel, all in one frag

    8 mapcels:
        1 index_t      8 bytes
        1 frag_ind_t  16
        1 array_t     68 bytes
        8 mapcels     64 bytes  156

    4 mapcels:
        1 index_t      8 bytes
        1 frag_ind_t  16
        1 array_t     36 bytes
        4 mapcels     32 bytes

    1 mapcel:
        1 index_t      8 bytes
        1 frag_ind_t  16
        1 array_t     12 bytes
        1 mapcels      8 bytes

4 mapcels vs 1 mapcel, all in diff frags

    8 mapcels:
        1 index_t      8 bytes
        8 frag_ind_t  128
        8 array_t     96 bytes
        8 mapcels     64 bytes  296


    4 mapcels:
        1 index_t      8 bytes
        4 frag_ind_t  64
        4 array_t     48 bytes
        4 mapcels     32 bytes  132

    1 mapcel:
        1 index_t      8 bytes
        1 frag_ind_t  16
        1 array_t     12 bytes
        1 mapcels      8 bytes  46

if mapcels contained frag info: ( extra 8 bytes per )

    8 mapcels
        1 array_t     68 bytes
        8 mapcels    128 bytes  196

    4 mapcels
        1 array_t     36 bytes
        4 mapcels     64 bytes  100

    1 mapcels
        1 array_t     12 bytes
        1 mapcels     16 bytes  28

Now with a 2:1 indexing ratio

if mapcels contained frag info: ( extra 8 bytes per )

    8 mapcels
        1 array_t     36 bytes
        8 mapcels    128 bytes  164

    16 mapcels
        1 array_t     36 bytes
       16 mapcels    256 bytes  292

if index contained frag info, diff frags:

    8 mapcels:
        1 index_t      8 bytes
        4 frag_ind_t  64 bytes
        4 array_t     48 bytes
        8 mapcels     64 bytes  180

    16 mapcels:
        1 index_t      8 bytes
        8 frag_ind_t  64 bytes
        8 array_t     68 bytes
        16 mapcels    96 bytes  236

if index contained frag info, same frag:

    8 mapcels:
        1 index_t      8 bytes
        1 frag_ind_t  16 bytes
        1 array_t     36 bytes
        4 dirent mapcels     64 bytes  124

    16 mapcels:
        1 index_t      8 bytes
        1 frag_ind_t  16 bytes
        1 array_t     68 bytes
        8 dirent mapcels 64 bytes
        8 mapcels     64 bytes  228


basically 2 longs of overhead per fragment if frag link is stored in the index.


acquiring a mapcel from an index and making it meaningful
---------------------------

a flat array of mapcels can represent a directory.  to find a certain mapcel you have to query the sub-mapcels or read the pattern under the mapcel.

eg. sections in a markdown text

each section is an element of the markdown DOM index.  but I find the section title meaningful.  i don't need to look at the whole section as a representation of the section.

the mapcel is the dirent.  but I want to search each mapcel for the section title and list the titles -- perhaps index the titles for faster lookup later.

maybe the index can be a property of access-path rather than dcel.

does it make more sense to build the index on the same pass as the initial data scan?  will that save time?