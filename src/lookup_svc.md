

see also design/architecture.md


`lookup_svc` provides service to lookup modules.  a lookup module must include `lookup_svc.h`


lookup svc functions operate on a `lookup_hdl`


a lookup creates a sequence of production instructions suitable for processing by the `production_core`.



`find_child()`
-------------

searches parent for child.

#) if parent is out of sync

    remap parent

#) 


examples
--------

lookup base.targetformat

may translate to:

base.mapper.formatter

production chain:

        sync and map "$parent"
        select * from "$parent->children" where "d_name" like "$base.%"
        map * from selection with mapper, where "mapper_name" like "mapper"
        bind_merge * from selection
        format bound_merged with formatter, where "formatter_name" like "formatter"


psuedocode:

        sync_and_map( $parent ) --> parent
        select_all_from_children_where_dname_like( $parent, $base_re ) --> sel
        map_all_from_selection( $sel, $mappername_re ) --> sel
        bind_merge_all( $sel ) --> merged
        format( $merged, $formatter_name_re ) --> formatted


example
-------

lookup filename

        select * from `$parent->children` where `d_name` is $filename


