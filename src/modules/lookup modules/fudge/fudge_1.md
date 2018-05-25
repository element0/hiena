fudge grammar
-------------

  fudgepath
    : pathseg ( / pathseg )*

  pathseg
    : selectexpr? ( . modifier )*


lookup behavior
---------------

a modifier expression is expanded via an alias list.  each alias may refer to an executable file and a string of arguments in CLI format.

the executible should be found via the PATH variable of the access frame.  the PATH automatically includes the current cosm/tools directory.

the executable may also be a shared object file.  if a shared object file is found, the cosmos db will be checked to see if it's already loaded.  the main function should be named "main".

recap:

two possible branches exist.  one, an external executable; two, a shared object function.

the prod instr may look like this:

  pi->fn = dgrind;
  pi->argv[0] = cmdname;
  pi->argv[1] = arg1;
  ...

where dgrind shines is this versitile behavior.  dgrind is where the branch logic is.

There is a single interface:

  dgrind( aframe, argc, argv );

argv[0] is the cmdname.  dgrind calls the cosmos_pathsearch() func.  

if the path search returns an external executable,

  dgrind_external( aframe, argc, argv );

the cmdname may include a slash.  in this case it indicates a function within a script or shared object file.

The pathsearch func uses argv[0] and the aframe/env/PATH variable to generate a list of pathstrings.  it uses cosmosdb to match those against the cosmosdb object cache.  if a path matches, its object is analyzed: if a shared object file, we append 'main' to the pathstring and search for the function.  if the object is a function, we use it:

  dgrind_fn( aframe, fn, argc, argv );


sample fudge
------------
  ls pathto/diskimg.carve-all/docx/.unzip/.grep-$STR-c/.grep-':[^0]'

