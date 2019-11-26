

see also "dfind.{c,h,md}"
see also "dcel_dirsvc.md"



lookup vs find
--------------
dcel_find returns a list.
lookup returns an item.

find is internal.
lookup is externalized via modules.

there is no dcel_lookup method.


dcel_find() list type
---------------------
(2018-05-06 0718)

list is implemented by a dcel.
dcel->child[index '\0']->suffix['\0'] is first element.





find interface
--------------

  dcel_find_child()
  dcel_find_child_by_prefix()
  dcel_find_child_by_regex()
  dcel_find_child_by_ordinal()


find by regex is most expensive op.
find child is least expensive.

find by prefix can be relatively inexpensive if the implementation uses a two layer tree, prefix locates leaf list (second layer) of suffix entries.  suffix entry locates target.


storage interface
-----------------


the converse of the above:

  dcel_mapsvc::new_dirent()
  dcel_add_child();



prefix, suffix keys implementation
----------------------------------

dcel child list key

  uintptr_t prefix,
  uintptr_t suffix


first uintptr_t is hash of file basename wout suffix

second is hash of suffix (with leading suffix separator)


dcel
  prefix btree
    suffix btree


uses:

  btree_cpp.h
  