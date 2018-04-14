
cosmos subsystem
----------------

"cosmos", the "Cascading Operating SysteM OS"


provides:
- file tree
- cascading os directories
- domain cells




cosmos
------

snafu.c

snafufs


cosmos.cpp


cosmosdb


string cache[] {
  hash key, string
}


access frame {
  branches[]
  dcel
}


branches[] {
  hash key, access frame
}

dcel {
  svc
  prod instr
  indices[]
  value type
  value
}

indices[] {
  index
}

index {
  member type
  ops
  members[] { key, dcel }
}

svc {
  ops
}

prod instr {
  svc
  op
  access frame
  argc
  argv
}