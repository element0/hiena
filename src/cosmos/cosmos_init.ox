cosmos
        cosmos init



cosmos init
        get cosmos db
        -or-
        create cosmos db
        init essential modules
        create proto cosm
        create user@host root



get cosmos db


create cosmos db
        cosmos db new
        aframe new
        dcel new
        

init essential modules
        init filesvc
        init lookupsvc


create user@host root
        cosmos_map_file(cm, filesvc, cosm_path, "host/user");


create proto cosm
        cosmos_map_file(cm, filesvc, cosm_path, ".cosm");


cosmos_map_file( cmdb, svc, src, dest )
    cosmos cd( cmdb root )
    cosmos mkdir( dest )
    dcel sourcer ( svc, src )
    store at( dest )

