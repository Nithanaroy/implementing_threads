/* Author1 name: Nitin Pasumarthy
   ID :1207666508
   email ID: npasumar@asu.edu */
 
/* Author1 name: Tanushree Chakravorty
   ID :1207664935
   email ID: tkchakra@asu.edu */

/* Author1 name: Alekhya Cheruvu
   ID :1209209296
   email ID: acheruvu@asu.edu */


#include <ucontext.h>
#include <stdio.h>
#include <string.h>

typedef struct _TCB_t {
	ucontext_t context;
	struct _TCB_t *prev;
	struct _TCB_t *next;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
	memset(tcb, '\0', sizeof(TCB_t));
	getcontext(&tcb->context);
	tcb->context.uc_stack.ss_sp = stackP;
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0);// context is now cooked


}
