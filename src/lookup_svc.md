

see also design/architecture.md


"lookup_svc" provides service to lookup modules.  a lookup module must include "lookup_svc.h"


lookup svc functions operate on a "lookup_hdl"


a lookup creates a sequence of production instructions suitable for processing by the production_core.



find_child()
------------

searches parent for child.

#) if parent is out of sync

    remap parent

#) 
