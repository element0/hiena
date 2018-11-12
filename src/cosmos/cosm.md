cosm directory design
---------------------
(date 2018-06-21)

  .cosm
      etc
          cosmos.conf
      lib
          cosmos
              init
                  mods
                      file.so
                      lookup.so
              mods
                  file.so
                  fudge.so
                  lookup.so



(date 2018-01-03)

various views which may be useful

        .cosm .ui
                tools
                types
                users

        .cosm .os
                conf
                svc
                xform

        .cosm .posix
                bin
                etc
                lib


example access paths to function pointers

  .cosm/svc/file/cosmos_mapfn

  .cosm/xform/cosm


