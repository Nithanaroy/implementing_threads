#include <stdio.h>
#include <stdlib.h>
#include "thread.h"


void function1(void);
void function2(void);
void function3(void);


TCB_t *runQ;


int total_count;

int main()
{
	runQ = (TCB_t*)malloc(sizeof(TCB_t));
	initQueue(runQ);

	startThread(function1);
	startThread(function2);
	startThread(function3);

	runQ();

	return 0;
}



void function1() /*does sum of all numbers */
{
	int sum = 0;

	printf("Thread1: Started \n");
	while (1)
	{

		total_count++;
		sum++;
		printf("Thread Count is %d \t and sum  is %d \t", total_count, sum);
		yield();
	}


}

void function2() /*gives 5 table output */
{
	int sum = 0;

	printf("Thread2: Started \n");
	while (1)
	{

		total_count++;
		sum = sum + 5;
		printf("Thread Count is %d \t and sum  is %d \t", total_count, sum);
		yield();
	}


}


void function3() /*gives 10 table output */
{
	int sum = 0;

	printf("Thread3: Started \n");
	while (1)
	{

		total_count++;
		sum = sum + 10;
		printf("Thread Count is %d \t and sum  is %d \t", total_count, sum);
		yield();
	}


}

