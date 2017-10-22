
dfind family of production functions
------------------------------------

as a production instruction, the production must hold if rerun on a changed domain.

if

   x{abcd}

was mapped so a b c d were children of x, then x/c should be the same even if

   x{acbd}

(the children are unordered)

however x[2] should return c in the first case, and b in the latter.

If a dcel is a product in reference to an ordinal address, its content would change.


dfind_child algorithm
---------------------

inputs:
    dcel
    ruleid
    value

implied:
    child table of src dcel

returns:
    dcel


return value:

will either be a single dcel or a dcel who's body is a sequence of selected dcels.

if the return dcel selects multiple dcels, they shall be included in the return cel's child list and their frags shall be concatenated in the return cel's frag.



dfind_prop algorithm
--------------------

inputs:
    dcel
    ruleid

implied:
    prop map of dcel

returns:
    dcel


return value:

will either be a single dcel or a dcel who's body is a sequence of selected dcels.


procedure:

  for each in input_dcel->prop
      if each->ruleid == ruleid
          add each to found_list

  if count > 1
      new_dcel->children = found_list
      append each->frag to new_dcel->frag

  if count == 1
      return each

      

          
