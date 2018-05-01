

see also "dfind.{c,h,md}"


lookup interface
----------------

  dfind_child_by_prefix()
  dfind_child()
  dfind_child_by_regex()
  dfind_child_by_ordinal()


find by regex is most expensive op.
find child is least expensive.

find by prefix can be relatively inexpensive if the implementation uses a two layer tree, prefix locates leaf list (second layer) of suffix entries.  suffix entry locates target.


storage interface
-----------------


the converse of the above:

  dcel_mapsvc::new_dirent()
  dcel_set_child();



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
  