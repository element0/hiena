cosmos module system
--------------------

- recording modules in db as dcels


recording modules in db as dcels
--------------------------------

dlopen filepath -> void *dl
dlsym module_ops -> void *ops_struct
fn_ptr = ops_struct/some_func

  dcel
    frag ptr = void *dl
    map
      "name": modname
    dir
      child[n] = dcel 2

  dcel 2
    frag ptr = void *ops_struct
    map
      "name": "ops"
    dir 2
      child[n] = dcel 3

  dcel 3
    frag ptr = void *fn_ptr
    map
      "name": funcname


  cosmos obj
    strings by hash id
    access frames by hash id

  aframe
    dcel = dcel
    child[n] = aframe 2

  aframe 2
    dcel = dcel 2
    child[n] = aframe 3

  aframe 3
    dcel = dcel 3

