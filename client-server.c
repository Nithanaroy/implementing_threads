#include "msgs.h"

#define SERVER_PORT 98
#define CLIENT_PORT 99

/* Author1 name: Nitin Pasumarthy
   ID :1207666508
   email ID: npasumar@asu.edu */
 
/* Author1 name: Tanushree Chakravorty
   ID :1207664935
   email ID: tkchakra@asu.edu */

/* Author1 name: Alekhya Cheruvu
   ID :1209209296
   email ID: acheruvu@asu.edu */


int temp=0;
TCB_t * Q;

void client1()
{

char **client_table;
client_table = (char **) malloc(5*sizeof(char *));
int j=0;
for(j=0;j<10;j++)
        client_table[j]=(char *)malloc(20*sizeof(char));

client_table[0]="abc";
client_table[1]="def";
client_table[2]="ghi";
client_table[3]="jkl";
client_table[4]="mno";


while(1){
P(&p[SERVER_PORT].empty);
  char *a;
a=(char *)malloc(40*sizeof(char));

char *c = (char *)malloc(1*sizeof(char));
int randnum = rand()%5;
c[0] = (char) ( ((int) '0') + randnum );
strcpy(a, c);

char *d = (char *)malloc(1*sizeof(char));
d[0]=(char)(((int)'0')+1);

strcat(a, d);
strcat(a,client_table[randnum]);

  send(&p[SERVER_PORT], a,SERVER_PORT);
  sleep(1);
V(&p[SERVER_PORT].full);
yield();
}
}

void client2()
{

char **client_table;
client_table = (char **) malloc(5*sizeof(char *));
int j=0;
for(j=0;j<10;j++)
        client_table[j]=(char *)malloc(20*sizeof(char));

client_table[0]="zzz123";
client_table[1]="zzz456";
client_table[2]="zzz789";
client_table[3]="zzz000";
client_table[4]="zzz111";



while(1){
P(&p[SERVER_PORT].empty);
  char *a;
a=(char *)malloc(40*sizeof(char));

char *c = (char *)malloc(1*sizeof(char));
int randnum = rand()%5;
c[0] = (char) ( ((int) '0') + randnum );
strcpy(a, c);

char *d = (char *)malloc(1*sizeof(char));
d[0]=(char)(((int)'0')+2);

strcat(a, d);
strcat(a,client_table[randnum]);


  send(&p[SERVER_PORT], a,SERVER_PORT);
  sleep(1);
V(&p[SERVER_PORT].full);
yield();
}
}

void client3()
{
while(1){
char **client_table;
client_table = (char **) malloc(5*sizeof(char *));
int j=0;
for(j=0;j<10;j++)
        client_table[j]=(char *)malloc(20*sizeof(char));

P(&p[CLIENT_PORT].full);
  if(temp++%3==0){
  printf("\n\t\t\tClient 3 recieve initiated\n");
  for(j=0;j<5;j++)
	  receive(&p[CLIENT_PORT],client_table[j],CLIENT_PORT);
  printf("\n\t\t\tClient 3 recieving\n");
  for(j=0;j<5;j++)
         printf("\n\t\t\t\t\t%s",client_table[j]);
	printf("\n");
  sleep(1);
}
V(&p[CLIENT_PORT].empty);
yield();
}
}

void server()
{
printf("Creating Server Table\n");
printf("======================\n");
char **server_table;
server_table = (char **) malloc(5*sizeof(char *));
int j=0;
for(j=0;j<10;j++)
	server_table[j]=(char *)malloc(20*sizeof(char));

server_table[0]="abc";
server_table[1]="def";
server_table[2]="ghi";
server_table[3]="jkl";
server_table[4]="mno";

for(j=0;j<5;j++)
	printf("%d:%s\n",j,server_table[j]);
printf("\n");


while(1){
P(&p[SERVER_PORT].full);
  char a[20],ch;
char *msg;
msg=(char*)malloc(20*sizeof(char));
  int i=2;
j=0;
  receive(&p[SERVER_PORT],a,SERVER_PORT);
  char c=a[0];
int ind = c-'0';

 c = a[1];
int clientid = c-'0';

  while((ch=a[i++])!='\0')
   msg[j++]=ch;

  server_table[ind]=msg;
  printf("\nServer Recieved modification from Client %d message: %s index %d\n",clientid,msg,ind);
  printf("====================================================================\n");
	int k=0;
  for(k=0;k<5;k++)
        printf("%d:%s\n",k,server_table[k]);
  printf("\n");
  sleep(1);
V(&p[SERVER_PORT].empty);

P(&p[CLIENT_PORT].empty);
  int j=0;
  for(j=0;j<5;j++)
	send(&p[CLIENT_PORT], server_table[j],CLIENT_PORT);
  sleep(1);
V(&p[CLIENT_PORT].full);
yield();


}
}


int main()
{   
   p[0].in=0; p[0].out=0;
   p[20].in=0; p[20].out=0;
   p[99].in=0; p[99].out=0;
    init_port();
	printf("\n\t\t\tCreating a client1");
    start_thread(client1);
	printf("\n\t\t\tCreating a client2");
    start_thread(client2);
	printf("\n\t\t\tCreating a client3");
    start_thread(client3);
	printf("\n\t\t\tCreating a server");
	printf("\n\t\t\t*******************\n");
    start_thread(server);
	run();
    while (1) sleep(1);
}   


