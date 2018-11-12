cosmos_fs explanation
---------------------

these are the fs functions that can be called from within fuse functions to implement a file system.


  cosmos_fs_stat();



cosmos_fs_stat
--------------


cosmos_fs_stat()

procedure:

    get dcel
    get dcel-protocol id
    get module from id
    run module->stat(dcel->addr)
