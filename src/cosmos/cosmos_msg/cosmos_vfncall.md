




VFNCallFrame
------------

VFCallFrame carries call frame and context to the VM to execute a function or executable. The VM uses the info to duplicate the calling environment.

VFCallFrame also carries idl information returned from cosmos_dlsym(): argv with sizes but no bodies, fnid with full value. this idl info is used by the caller to build a calling VFCallFrame.

VFCallFrame carries VM control calls like, cosmos_dlopen() and cosmos_dlsym(). The control functions are standardized and pre-numbered and their idl's are included at compile time.

VFCallFrame carries return values and modified environment.