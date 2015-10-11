#include <ucontext.h>
# include <stdio.h>
# include <string.h>
# include "q.h"

struct TCB_t{
	ucontext_t context;
	struct TCB_t *prev;
	struct TCB_t *next;
};

void init_TCB (TCB_t *tcb,void *function,void *stackP,int stack_size)
{
	memset(tcb, '\0', sizeof(TCB_t));       
	getcontext(&tcb->context);             
	tcb->context.uc_stack.ss_sp = stackP;
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0);// context is now cooked


}
