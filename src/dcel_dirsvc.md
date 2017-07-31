








dcel_dirsvc
===========


contents
--------
- opendir algorithm
- readdir algorithm
- closedir algorithm



opendir algorithm
-----------------
prepare directory handle for reading

inputs:
- dcel

outputs:
- directory handle {}
  - directory structure
  - directory position
  - directory cache structure
  - directory cache position

procedure:




readdir algorithm
-----------------
get one dirent at a time

inputs:
- dcel
- directory structure via opendir
- directory handle via opendir: {}
    - position
    - length remaining
    - current map anchor
- directory cache structure
    - location

outputs:
- dirent
- update directory handle's position
- update dcel's directory cache


procedure:
- if dcel's dir cache is not stale
    - get dirent from cache loc
    - advance cache location
    - return dirent
-else-
- get map anchor at dir handle's pos
- for each in anchor's child list where length is less than "length remaining plus one":
    - create dirent from child
    - add dirent to dcel's dir cache
    - return dirent

internal vars:
- child list cursor



closedir algorithm
------------------
cleanup directory handle

inputs:
- directory handle

outputs:
- errno
