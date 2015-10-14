#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "unistd.h"


void function1(void);   /*declaration of function1 which calculates 2 table */
void function2(void);   /*declaration of function2 which calculates 5 table */
void function3(void);   /*declaration of function3 which calculates 10 table */

int total_count;        /* global count to keep the track of thread executed till that time */

int main()
{
	
	start_thread(function1);   /* assigning 1st thread with function1 */
	start_thread(function2);   /* assigning 2nd thread with function2 */
	start_thread(function3);   /* assigning 3rd thread with function3 */

	run();                     /* starting the threads */

	return 0;
}



void function1() /*Computes 2 table and provides output*/
{
	int sum = 0;
	int i = 0;

	printf("Thread1: Started \n");  /* to indicate thread got started */
	while (1)
	{
		i++;
		total_count++;             /* to get the global thread count */
		sum = sum + 2;
		printf("Thread global count is %d \n ", total_count);
		printf("Printing 2 table !!! \t\t\t");
		printf("Thread 1: 2*%d=%d \n\n\n", i, sum);
		yield();
		fflush(stdout);           /* to flush the contents of the buffer */
		sleep(1);                 
	}
}

void function2() /*Computes 5 table and provides output */
{
	int sum = 0;
	int i = 0;

	printf("Thread2: Started \n"); /* to indicate thread got started */
	while (1)
	{

		total_count++;            /* to get the global thread count */
		i++;
		sum = sum + 5;
		printf("Thread global count is %d \n", total_count);
		printf("Printing 5 table !!!\t\t\t");
		printf("Thread 2: 5*%d=%d \n\n\n", i, sum);
		yield();
		fflush(stdout);          /* to flush the contents of the buffer */
		sleep(1);
	}


}


void function3() /* Computes 10 table and provides output */
{
	int sum = 0;
	int i = 0;

	printf("Thread3: Started \n");  /* to indicate thread got started */
	while (1)
	{
		printf("Printing 10 table\n");
		i++;
		total_count++;             /* to get the global thread count */
		sum = sum + 10;
		printf("Thread global count is %d \n", total_count);
		printf("Printing 10 table !!!\t\t\t");
		printf("Thread 3: 10*%d=%d \n\n\n", i, sum);
		yield();
		fflush(stdout);           /* to flush the contents of the buffer */
		sleep(1);
	}


}

