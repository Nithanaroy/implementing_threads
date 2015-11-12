#include "Sem.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 10

int buff[SIZE];
int pi, ci;	/* producer and consumer indices for buffer */

Semaphore_t *full;
Semaphore_t *empty;

Semaphore_t *pmutex;
Semaphore_t *cmutex;

int DEBUG = false;

struct timespec half = {0, 50000L} , quarter = {0, 100000000L};

/**
 * To get a feel for random yeilds and switching to the next thread in the ReadyQ
 */
void randomly_yield() {
	int r = get_random();
	if (r % 3 == 0) {
		if (DEBUG)
		{
			printf("Yielding. Random (%d)\n", r);
			fflush(stdout);
		}
		yield();

	}
}

int get_random() {
	int r = rand();
	return r % 100;
}

void print_buffer() {
	int i = 0;
	for (i = 0; i < SIZE; ++i)
	{
		printf("%d ", buff[i]);
	}
	printf("\n");
}

void producer() {
	int r;
	int id = get_random();
	while (1) {
		P(&full);

		r = get_random();
		printf("%d: Produced: %d\n", id, r);

		P(&pmutex);
		buff[pi] = r;
		pi = (pi + 1) % SIZE;
		V(&pmutex);

		V(&empty);
		nanosleep(&half, NULL);
		randomly_yield();
	}
}

void consumer() {
	int c;
	int id = get_random();
	while (1) {
		P(&empty);

		P(&cmutex);
		c = buff[ci];
		print_buffer();
		printf("%d: Consumed: %d\n\n", id, c);
		ci = (ci + 1) % SIZE;
		V(&cmutex);

		V(&full);
		sleep(1);
		randomly_yield();
	}
}

int main(int argc, char const *argv[])
{
	srand(time(NULL)); /* For random number generator function */

	CreateSem(&full, SIZE);
	CreateSem(&empty, 0);
	CreateSem(&pmutex, 1);
	CreateSem(&cmutex, 1);

	start_thread(producer);
	start_thread(producer);
	start_thread(consumer);
	start_thread(consumer);
	start_thread(consumer);

	run();
	return 0;
}
