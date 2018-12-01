#ifndef _COSMOS_VM_CORE_H_
#define _COSMOS_VM_CORE_H_


/** a reusable vm core.
 */

struct cosmos_vm {

        /** capabilities profile compared with library and exec requirements profile.
         */

        void *profile;

        /** functions which open, link and exec.
         */

        void *(*libopen)(char *);
        int (*libclose)(void *);
        void *(*libsym)(void *, char *);
        void *(*exec)(void *);


        /** open libraries
         */

        int open_libs_size;
        int open_libs_count;
        void *open_libs[];


        /** open functions:
         maps between fnid and fnptr
         */

        int open_fns_size;
        int open_fns_count;
        uintptr_t *open_fns[];

};



#endif /* ! _COSMOS_VM_CORE_H_ */
