#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "thread.h"

typedef struct semaphore{
	int value;                           /*semaphore structure having value and semaphore queue */
	TCB_t  *semQ;
} Semaphore_t;

Semaphore_t *reader_Sem;
Semaphore_t *writer_Sem;                       /* pointer for the semaphore structure */



Semaphore_t * CreateSem(int  num)       /* creating the semaphore and initilaizing it's value */
{
	
		Semaphore_t *sem=(Semaphore_t *) malloc(sizeof(Semaphore_t));
		sem->value=num;
		sem->semQ=NULL;

		return sem;
}


void P(Semaphore_t **sem)               /* p operation of semaphore */
{

		(*sem)->value=(*sem)->value-1;      /* decrementing the value */
	    
	    if((*sem)->value < 0)            /* if less than 0 blocking the current process on sempahore queue */
	    {
	    	    TCB_t *temp;          
	    	    temp=DelQ(&runQ,runQ);
	    	    AddQ((*sem)->semQ,temp);
	    	    ucontext_t from,to;
	    	    getcontext(&from);
		    runQ->context=from;
	    	    to=temp->context;
	    	    swapcontext(&from,&to);	
	    }


}




void V(Semaphore_t **sem)
{
		(*sem)->value=(*sem)->value +1;      /* incrementing the value of sempahore */

		if((*sem)->value <=0)
		{
			TCB_t *temp;               /* deleting the element from semaphore q and putiing it on runQ */ 
			temp=DelQ(&runQ, (*sem)->semQ);
			AddQ(runQ,temp);
		}
 
}
