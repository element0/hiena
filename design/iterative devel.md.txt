

iterative development
---------------------


v 1
-------

snafufs calls cosmosd_init() and cosmosd file system calls directly.

there is no socket or cosmos_client implemented.


v 2
-------

snafufs calls cosmos_client().

cosmosd sockets and messages are implemented.

there are no grid procedures implemented with the prodexec function.

v 3
-------

prodexec implements a grid dispatch to execute production functions on other machines.

comsosd adds a grid protocol to its language.

cosmos adds ssh tunneling with a cosmos_visitor process which communicates with the cosmosd on a remote host.

v 4
-------

persistent on disk databases added to cosmosd.
