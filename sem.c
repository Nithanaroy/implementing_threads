#include "sem.h"

int total_count = 0;

Semaphore_t *sem;

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
		fflush(stdout);
		sleep(1);
	}
}


int main(int argc, char const *argv[])
{
	start_thread(function1);
	Semaphore_t * s = CreateSem(0);
	P(s);
	return 0;
}


