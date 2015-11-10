
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "msgs.h"


#define SERVER_PORT1	99



int	client_port  = 0;
semaphore_t*	client_Sem;

int main(int argc,char** argv)
{
	
	client_Sem = CreateSem(&client_Sem,1);

	
	start_thread(server);

	start_thread(client);
	start_thread(client);
	start_thread(client);


	run();

}



void server()
{
	int send_msg[10];
	int rcv_msg[10];
	int i;
	int reply_port;	



	while(1){
		
		recv(SERVER_PORT1,rcv_msg);

		
		reply_port = rcv_msg[0];  
		printf("received message from the client at port %d ", reply_port); /* asuming reply port is at index 0*/
		for(i = 1;i < 10;i++){
			printf("%d  ",rcv_msg[i]);
		}
		printf("\n");

		for(i = 1;i < 10;i++)
			send_msg[i-1] = rcv_msg[i]*2;
		send_msg[0]=SERVER_PORT1;	
		send(reply_port,send_msg);
		
		sleep(1);
	}
}




void client()
{
	
	int send_msg[10];
	int recv_msg[10];
	int i;
	int reply_port;

	P(client_Sem);
	reply_port = client_port++;
	V(client_Sem);

	for(i = 1;i < 10;i++){
		send_msg[i] = i*10;
	} 
	send_msg[0] = reply_port;

	while(1){
		
		send(SERVER_PORT1,send_msg);
		recv(reply_port,recv_msg);
		printf("received message from the server at port %d ", recv_msg[0]);
		
		printf("received message details\n");
		for(i = 1; i < 10 ; i++){
			printf("%d ",recv_msg[i]);
		}
		printf("\n");

		sleep(1);
	}
}


