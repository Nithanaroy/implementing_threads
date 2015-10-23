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
#include "Sem.h"

void reader(void);
void writer(void);

int a[5];
int total_count, reader_count, writer_count;

Semaphore_t *reader_Sem;  /* reader semaphore */
Semaphore_t *writer_Sem;  /* writer seamphore */
     
int main()
{
	CreateSem(&reader_Sem, 3);  /* multiple readers 3 at a time */
	CreateSem(&writer_Sem, 1);  /* single writer */

	
	start_thread(reader);       /* reader staring */
	start_thread(reader);       /* reader staring */
	start_thread(writer);       /* writer starting */
	start_thread(reader);       /* reader staring */

	run();			    /* starting the reads */

	return 0;
}


void reader()
{
	int i;                
	while (1)
	{
		P(&reader_Sem);   /* wait for other readers to increment the count */
		reader_count++;  /* incrementing count */
 		total_count++;   /* incrementing total count */
		if (reader_count == 1) 
		{
			P(&writer_Sem); /* waiting the writer thread */
		}
		V(&reader_Sem);         /* signal other readers */
		printf(" thread count is %d  \n", total_count);  /* printing thread count and reader count */
		printf("Reader reading  the contents of  array\n");                                      /* reading the contents of the array */
		for (i = 0; i < 5; i++)
		{ 
			printf("%d\t", a[i]);          /* printing the contents of the array */
		}
		printf("\n");

    
		P(&reader_Sem);                      /* blocking readers */
		reader_count--;                      /* decrementing the count */
		if (reader_count == 0)               /* check if readers count is 0 or not */
			V(&writer_Sem);              /* signaling the writers */

		V(&reader_Sem);                      /* signaling other writers */
		sleep(2);                            /* sleep */
		yield();	                     /* THIS IS A MUST */
	}
}


void writer ()
{
	int i;
	while (1)
	{
		P(&reader_Sem);                  /* blocking the reader */
		P(&writer_Sem);                  /* blocking the other writer */

		writer_count++;                  /* incrementing writers count */
		total_count++;                   /* incrementing total count */
		printf(" thread count is %d \n", total_count); /* printing the details */
		printf("Writer writing on the array\n");                                               /* printing the details of array */

		for (i = 0; i < 5; i++)           
		{
			a[i]++;
			printf("%d\t", a[i]);
		}

		printf("\n");
 
		V(&writer_Sem);                 /* releasing the lock */ 
		V(&reader_Sem);                 /* releasing the reader lock */
		sleep(2);
		yield();	                /* THIS IS A MUST */
	}
}
