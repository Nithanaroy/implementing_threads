#include <stdio.h>
#include <stdlib.h>
#include "q.h"


void start_thread(void(*function)(void));
void run();
void yield();

 TCB_t *runQ;


void start_thread(void (*function)(void))
{   // begin pseudo code
    TCB_t *item = (TCB_t*)malloc(sizeof  (TCB_t));
    if (item)
    {
        item->next = NULL;
        item->prev = NULL;
    }
    void *stack = (void*)malloc(8192);
    init_TCB(item, function, stack, 8192);
    addQ(runQ, item);

}

void run()
{   ucontext_t from, to, parent;
    parent = from;
    getcontext(&parent);
    to = runQ->context;
    swapcontext(&parent, &to);
}
void yield() // similar to run
{
    ucontext_t from, to;
    getcontext(&from);
    runQ->context = from;
    rotQueue(runQ);
    to = runQ->context;
    swapcontext(&from, &to);

}
