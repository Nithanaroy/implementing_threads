#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

typedef struct semaphore {
	int value;                           /*semaphore structure having value and semaphore queue */
	TCB_t  *semQ;
} Semaphore_t;

Semaphore_t * CreateSem(Semaphore_t **sem, int  num)       /* creating the semaphore and initilaizing it's value */
{
	(*sem) = (Semaphore_t *) malloc(sizeof(Semaphore_t));
	(*sem)->value = num;
	(*sem)->semQ = NULL;

	return *sem;
}


/**
 * Pre-Condition: runQ shouldn't be NULL
 * @param sem semaphore
 */
void P(Semaphore_t **sem)               /* p operation of semaphore */
{

	(*sem)->value = (*sem)->value - 1;  /* decrementing the value */

	if ((*sem)->value < 0)           /* if less than 0 blocking the current process on sempahore queue */
	{
		TCB_t *temp;
		temp = DelQ(&runQ, runQ);
		if ((*sem)->semQ == NULL) /* if the item is the 1st node then queue pointer should point the item */
		{
			InitQ(temp);
			(*sem)->semQ = temp;
		}
		else
		{
			AddQ(&((*sem)->semQ), temp);
		}

		ucontext_t from, to;
		getcontext(&from);					// main
		to = temp->context;					// function1
		swapcontext(&from, &to);
	}


}




void V(Semaphore_t **sem)
{
	(*sem)->value = (*sem)->value + 1;   /* incrementing the value of sempahore */

	if ((*sem)->value <= 0)
	{
		TCB_t *temp;               /* deleting the element from semaphore q and putiing it on runQ */
		temp = DelQ(&runQ, (*sem)->semQ);
		AddQ(&runQ, temp);
	}
	// yield();
}
