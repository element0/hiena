Domain Cell Map Service
=======================













## mapping nested cels efficiently ##

if new cel's pos is same as cur pos
    add to mapanchor at cur pos
else
    wait until "add" function
    when add child to new cel
    take the first child's anchor

implementation:
    dcel_mapsvc_new_term
        finds deepest map anchor 
    dcel_mapsvc_new
        does not find anchor
    dcel_mapsvc_add
        use first child anchor

## put new map cell ##

inputs:
  rule id
  length
  frag cursor:
      root cursor node:
          frag, frag offset
      current cursor node:
          frag, frag offset,
          outer cursor node
              ...
      current map anchor


outputs:
  new map cell
  updated frag cursor:
      current cursor node:
          frag, frag offset,
          outer cursor node
              ...
      current map anchor


procedure:

- find the deepest fragment which accomodates length

- create new mapcel from rule id and length

- get head and tail anchors for mapcel within fragment

- store new mapcel at anchors by rule id


## create new mapcel from rule id and length ##
aka("mapcel_new()")


## get head and tail anchors within fragment for mapcel ##

in:
  fragment
  offset
  length

out:
  head anchor
  tail anchor

procedure:
  btree insert algorithm
  returns value if exists
  otherwise generates new value

  for head anchor at offset
  for tail anchor at offset + length
  


## find the deepest fragment which accomodates length ##
aka( fragcurse_deepest_has_room )

in:
  length
  frag cursor:
      root cursor node:
          frag, frag offset
      current cursor node:
          frag, frag offset,
          outer cursor node
              ...
      current map anchor

out:
  updated frag cursor:
      root cursor node:
          frag, frag offset
      current cursor node:
          frag, frag offset,
          outer cursor node
              ...

procedure:

    @ does fragment have room?
        ( frag_has_room() )

    -yes-    `fcf:`
    @ find child fragment
        ( bnode_value_at_key_or_nearest_lesser() )

    @ does ( child ) fragment have room?
        ( frag_has_room() )

        -yes-
        step into child fragment
        repeat `fcf`

        -no-
        update cursor
            to frag, frag offset


    -no-     `fpf:`
    step out to parent fragment
    @ does fragment have room?
        ( frag_has_room() )

        -no-
        goto `fpf`

        -yes-
        update cursor
            to frag, frag offset


### find child fragment ###
### search fragment btree for offset ###
aka( frag_child_contains_offset() )
aka( bnode_value_at_key_or_nearest_lesser )

in:
  btree
  desired key (offset)

out:
  value at key (frag)
  found key (offset)

procedure:
  btree insert operation
  without insert

  nearest key <= offset

  at btree node
  get range of keys
  split range
  select range which holds offset
  split range...
  until ranges are one key each
  if key is eq. to offset
    child frag is value at key
    child offset is 0
  if no branch links
    child frag is key < offset
    child offset is offset - key
  else
    repeat `at btree node` at appropriate branch link





### does fragment have room? ###
aka( frag_has_room() )

in:
  fragment
      length
  offset
  length

out:
  TRUE -or- FALSE


procedure:
  if length + offset is less than fragment's length return TRUE else FALSE


