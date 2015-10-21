#include<stdio.h>
#include<stdlib.h>
#include "Sem.h"

void reader(void);
void writer(void);

int a[5];
int total_count, reader_count, writer_count;



int main()
{
	reader_Sem=CreateSem(1);
	writer_Sem=CreateSem(1);
	

		start_thread(writer);
		start_thread(writer);
		start_thread(reader);
		start_thread(writer);
	        /*start_thread(reader);*/
	        /*start_thread(writer);*/
		run();



	return 0;

}


void reader()

{	
	int i;
	while(1)
	{
		P(&reader_Sem);
			reader_count++;
			total_count++;
		if(reader_count==1)
			{
				P(&writer_Sem);
			}
		V(&reader_Sem);
		printf(" thread count is %d ,reader thread count is %d \n",total_count,reader_count);
	 	printf("Reader reading  the contents of  array\n");
		for(i=0;i<4;i++)
		{	
			printf("%d\t",a[i]);
		}
			printf("\n");	

		
		P(&reader_Sem);
			reader_count--;
			if(reader_count==0)
			  V(&writer_Sem);

		V(&reader_Sem);
		sleep(2);
	}
}

void writer ()
{
	int i;
	while(1)
	{	
		P(&reader_Sem);
		writer_count++;
		total_count++;
		printf(" thread count is %d ,writer thread count is %d\n",total_count,writer_count);
		 printf("Reader reading  the contents of  array\n");
		 printf("Writer writing on the array\n");
	
		for(i=0;i<5;i++)
		{
			a[i]++;
		}

		for(i=0;i<5;i++)
		{
			printf("%d\t",a[i]);
		}
		printf("\n");	

       	    V(&reader_Sem);
	    sleep(2);

	}
}
