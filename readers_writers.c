#include <stdio.h>
#include <stdlib.h>
#include "Sem.h"

void reader(void);
void writer(void);

int a[5];
int total_count, reader_count, writer_count;

Semaphore_t *reader_Sem;
Semaphore_t *writer_Sem;                       /* pointer for the semaphore structure */

int main()
{
	CreateSem(&reader_Sem, 3);
	CreateSem(&writer_Sem, 1);

	start_thread(writer);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);

	run();

	return 0;
}


void reader()
{
	int i;
	while (1)
	{
		P(&reader_Sem);
		reader_count++;
		total_count++;
		if (reader_count == 1)
		{
			P(&writer_Sem);
		}
		V(&reader_Sem);
		printf(" thread count is %d ,reader thread count is %d \n", total_count, reader_count);
		printf("Reader reading  the contents of  array\n");
		for (i = 0; i < 5; i++)
		{
			printf("%d\t", a[i]);
		}
		printf("\n");


		P(&reader_Sem);
		reader_count--;
		if (reader_count == 0)
			V(&writer_Sem);

		V(&reader_Sem);
		sleep(2);
		yield();	/* THIS IS A MUST */
	}
}


void writer ()
{
	printf("Came to writer\r\n");
	int i;
	while (1)
	{
		P(&reader_Sem);
		P(&writer_Sem);

		writer_count++;
		total_count++;
		printf(" thread count is %d ,writer thread count is %d\n", total_count, writer_count);
		printf("Writer writing on the array\n");

		for (i = 0; i < 5; i++)
		{
			a[i]++;
			printf("%d\t", a[i]);
		}

		printf("\n");

		V(&writer_Sem);
		V(&reader_Sem);
		sleep(2);
		yield();	/* THIS IS A MUST */
	}
}
