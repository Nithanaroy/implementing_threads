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
	int threadID = 1;

	printf("Thread1: Started \n");
	while (1)
	{

		total_count++;
		sum++;
		printf("Thread ID: %d is %d and sum  is %d \n", threadID, total_count, sum);
		yield();
		fflush(stdout);
		sleep(1);
	}
}

void function2() /*gives 5 table output */
{
	int sum = 0;
	int threadID = 2;

	printf("Thread2: Started \n");
	while (1)
	{

		total_count++;
		sum = sum + 5;
		printf("Thread ID: %d is %d and sum  is %d \n", threadID, total_count, sum);
		yield();
		fflush(stdout);
		sleep(1);
	}


}


void function3() /*gives 10 table output */
{
	int sum = 0;
	int threadID = 3;

	printf("Thread3: Started \n");
	while (1)
	{

		total_count++;
		sum = sum + 10;
		printf("Thread ID: %d is %d and sum  is %d \n", threadID, total_count, sum);
		yield();
		fflush(stdout);
		sleep(1);
	}


}

