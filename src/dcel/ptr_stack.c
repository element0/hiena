

#include <stdlib.h>
#include <string.h>
#include "ptr_stack.h"
#include "hierr.h"

#define PTR_STACK_DEFAULT_DEPTH

struct linked_item
{
        struct linked_item *prev;
        struct linked_item *next;
        void *ob;
};

/* opaque structure */

struct ptr_stack
{
        struct linked_item *base;
        struct linked_item *top;
};



ptr_stack_t ptr_stack_new()
{
        struct ptr_stack *p;

        p = malloc(sizeof(*p));
        memset(p,0,sizeof(*p));

        return (ptr_stack_t)p;
}


static struct linked_item *linked_item_new()
{
        struct linked_item *li;

        li = malloc(sizeof(*li));
        memset(li,0,sizeof(*li));

        return li;
}


int ptr_stack_cleanup(ptr_stack_t pp)
{
        if( pp == NULL )
        {
                HIERR("ptr_stack_cleanup: err: pp NULL");
                return -1;
        }

        struct ptr_stack *p;
        struct linked_item *top;

        p = (struct ptr_stack *)pp;

        top = p->top;
        while( top != NULL )
        {
                p->top = top->prev;
                free(top);
                top = p->top;
        }
        free(p);

        return 0;
}


static int linked_item_cleanup(struct linked_item *li)
{
        if( li == NULL )
        {
                HIERR("linked_item_cleanup: err: li NULL");
                return -1;
        }
        free(li);

        return 0;
}


int ptr_stack_push(ptr_stack_t pp, void *ptr)
{
        if(pp == NULL)
        {
                HIERR("ptr_stack_push: err: pp NULL");
                return -1;
        }

        struct ptr_stack *p;
        struct linked_item *li;
        struct linked_item *top;

        p = (struct ptr_stack *)pp;

        li = linked_item_new();
        if( li == NULL )
        {
                HIERR("ptr_stack_push: err: linked_item_new() NULL");
                return -1;
        }

        li->ob = ptr;

        top = p->top;
        if( top == NULL )
        {
                p->top = li;
                p->base = li;

                return 0;
        }

        li->prev = top;
        top->next = li;
        p->top = li;
        
        return 0;
}


void *ptr_stack_pop(ptr_stack_t pp)
{
        struct ptr_stack *p;
        struct linked_item *top;
        struct linked_item *prev;
        void *res;


        p = (struct ptr_stack *)pp;
        if(p == NULL)
        {
                HIERR("ptr_stack_pop: err: p NULL");
                return NULL;
        }


        top = p->top;
        if( top == NULL )
                return NULL;

        res = top->ob;
        prev = top->prev;
        linked_item_cleanup( top );

        p->top = prev;
        if( prev != NULL )
                prev->next = NULL;

        return res;
}




void *ptr_stack_top(ptr_stack_t pp)
{
        if(pp == NULL)
        {
                HIERR("ptr_stack_pop: err: pp NULL");
                return NULL;
        }

        struct ptr_stack *p;
        struct linked_item *top;

        p = (struct ptr_stack *)pp;
        top = p->top;

        if(top == NULL)
        {
                HIERR("ptr_stack_pop: err: top NULL");
                return NULL;
        }

        return top->ob;
}


