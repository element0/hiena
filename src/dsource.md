dsource
-------


inputs:

access frame of module (ie. filesvc)
int argc  (==1)
void argv (argv[0] address)


outputs:

dcel


procedure:

the module is queried for sourcer_fn.

create prod instr w sourcer_fn

run prod instr to create dcel