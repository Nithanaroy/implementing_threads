#include <ucontext.h>
#include <stdio.h>
#include <string.h>

typedef struct _TCB_t {    /*structure which contains the next and prev pointers of the nodes */
	ucontext_t context;
	struct _TCB_t *prev;
	struct _TCB_t *next;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)  
{
	memset(tcb, '\0', sizeof(TCB_t));
	getcontext(&tcb->context);          /* intializing the TCB of the thread and giving the runner function */
	tcb->context.uc_stack.ss_sp = stackP;
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0);


}
