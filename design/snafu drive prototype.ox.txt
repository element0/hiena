
snafu mount
   root
   host cosm
   cosmosdb

root .dcel
   prod instr: src/file $mountpoint
   frag/mfrag
      addr: $mountpoint
      svc:  src/file
   childr
      $example

src/file .dcel

src/dl .dcel

scan/dlsym .dcel

----

mountpoint
   example

example
   part 1
      "stuff can be put here
   part 2
      "other stuff over here

example .dcel
   prod instr: scan/ox $example
   childr 
      part 1
      part 2


----

host cosm .dcel
   prod instr: dcel-cosm $"host cosm source"
   children: 

host cosm source .dcel
   prod instr: src/file $hostcosmdir
   frag/mfrag
      addr: $hostcosmdir
      svc:  file