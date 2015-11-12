
/* Author1 name: Nitin Pasumarthy
   ID :1207666508
   email ID: npasumar@asu.edu */
 
/* Author1 name: Tanushree Chakravorty
   ID :1207664935
   email ID: tkchakra@asu.edu */

/* Author1 name: Alekhya Cheruvu
   ID :1209209296
   email ID: acheruvu@asu.edu */



#include <stdio.h>
#include <stdlib.h>
#include "q.h"


void start_thread(void(*function)(void));  
void run();
void yield();

TCB_t *runQ = NULL;


void start_thread(void (*function)(void)) {   /* starts the thread */
    TCB_t *item = create_node();              /* creates a node of type TCB_t */
    void *stack = (void*)malloc(8192);        /* allocates stac memory */
    init_TCB(item, function, stack, 8192);    /* allocates the function for the item to run */
    if (runQ == NULL)                         /* if the item is the 1st node then queue pointer should point the item */
    {
        InitQ(item);
        runQ = item;
    }
    else {          
        AddQ(&runQ, item);                     /* add the item to the run queue */
    }
}

void run()                                    
{   ucontext_t from, to, parent;
    parent = from;
    getcontext(&parent);            /* swaps the main context with the context present in the queue because this is given by main */    
    to = runQ->context;
    swapcontext(&parent, &to);
}
void yield()      
{
    ucontext_t from, to;
    getcontext(&from);
    runQ->context = from;          /* whenever the function calls yield it does the swap context */
    RotateQ(&runQ);                /* with the other thread perent in the queue */
    to = runQ->context;
    swapcontext(&from, &to);
    
}
