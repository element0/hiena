#ifndef HIENA_POINTER_STACK
#define HIENA_POINTER_STACK


typedef void * ptr_stack_t;


ptr_stack_t ptr_stack_new();

int ptr_stack_cleanup(ptr_stack_t);

int ptr_stack_push(ptr_stack_t, void *);

void *ptr_stack_pop(ptr_stack_t);

void *ptr_stack_top(ptr_stack_t);

#endif /* !HIENA_POINTER_STACK */
