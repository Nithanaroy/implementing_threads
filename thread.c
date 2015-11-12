#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "unistd.h"


void function1(void);
void function2(void);
void function3(void);


int total_count;  

int main()
{
	// runQ = create_node();
	// InitQ(runQ);

	start_thread(function1);
	start_thread(function2);
	start_thread(function3);

	run();

	return 0;
}



void function1() /*does sum of all numbers */
{
	int sum = 0;
	int i = 0;

	printf("Thread1: Started \n");
	while (1)
	{
		i++;
		total_count++;
		sum = sum + 2;
		printf("Thread global count is %d \n ", total_count);
		printf("Printing 2 table !!! \t\t\t");
		printf("Thread 1: 2*%d=%d \n\n\n", i, sum);
		yield();
		fflush(stdout);
		sleep(1);
	}
}

void function2() /*gives 5 table output */
{
	int sum = 0;
	int i = 0;

	printf("Thread2: Started \n");
	while (1)
	{

		total_count++;
		i++;
		sum = sum + 5;
		printf("Thread global count is %d \n", total_count);
		printf("Printing 5 table !!!\t\t\t");
		printf("Thread 2: 5*%d=%d \n\n\n", i, sum);
		yield();
		fflush(stdout);
		sleep(1);
	}


}


void function3() /*gives 10 table output */
{
	int sum = 0;
	int i = 0;

	printf("Thread3: Started \n");
	while (1)
	{
		printf("Printing 10 table\n");
		i++;
		total_count++;
		sum = sum + 10;
		printf("Thread global count is %d \n", total_count);
		printf("Printing 10 table !!!\t\t\t");
		printf("Thread 3: 10*%d=%d \n\n\n", i, sum);
		yield();
		printf("After yield() check\n");
		fflush(stdout);
		sleep(1);
	}


}

