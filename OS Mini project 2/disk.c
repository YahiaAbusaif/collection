#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
struct msgbuff
{
	long mtype;
	char mtext[65];
};



char memory[10][64]; //memory 
int empty[10]; //check if slot is free
int cnt=10; //number of free slot 
int end;
int clock=0;

struct msgbuff message;
pid_t pid;
key_t up;
key_t down;

void sendStatus(int signum);
void IncClock(int signum);
void END(int signum);

void store(char *msg)
{ 
	if(sizeof(message.mtext)<2)
		return;
	char res[2];
	int i;
	end=clock;
	if(msg[0]=='D')
	{
		end=clock+1;
		if(empty[msg[1]-'0']==0)
		{
			empty[(msg[1]-'0')]=1;
			cnt++;
			strcpy(res,"1");
		}
		else
		{
			strcpy(res,"3");
		}
	}
	else if(msg[0]=='A')  
	{
		end=clock+3;
		if(cnt==0)
			strcpy(res,"2");
		else
		{
			for (i=0; i<10; i++)
			{
				if(empty[i]==1)
					break;
			}
			strncpy(memory[i],msg+1,sizeof(msg)-1);
			empty[i]=0;
			cnt--;
			strcpy(res,"0");
		}		
		
	}
	strcpy(message.mtext,res);
}


int main()
{
	up = msgget(888, IPC_CREAT|0644);
	down = msgget(777, IPC_CREAT|0644);
	signal (SIGUSR1, sendStatus);
	signal (SIGUSR2, IncClock);
	signal (SIGINT, END);
	int i=0,send_val,rec_val;
	for(i=0;i<10;i++)
		empty[i]=1;
	
	message.mtype=getpid();
	send_val = msgsnd(up, &message, sizeof(message.mtext), !IPC_NOWAIT);
	  		
	while(1)
	{
  		rec_val = msgrcv(down, &message, sizeof(message.mtext), 0, !IPC_NOWAIT);  
		if(rec_val != -1)
		{
			printf("massage has been recived %s\n",message.mtext);
			store(message.mtext);
			printf("massage will be send %s\n",message.mtext);
			while(end!=clock) {}
		  	send_val = msgsnd(up, &message, sizeof(message.mtext), !IPC_NOWAIT);
		  	if(send_val == -1)
		  		printf("Erorr in send result\n");
			else
				printf("massage had been send \n");
		}
	}
	return 0;
}


void sendStatus(int signum)
{
	struct msgbuff bmessage;
 	int send_val;
	bmessage.mtext[0]=cnt;
	bmessage.mtype=getpid();
	send_val = msgsnd(up, &bmessage, sizeof(bmessage.mtext), !IPC_NOWAIT);  
	if(send_val == -1)
	  	printf("Erorr in send count\n");
}
void IncClock(int signum)
{
	printf("clock increament by 1\n");
	int i=0;
	for(i=0;i<10;i++)
	{
		if(empty[i])
			printf("%d: free   ",i);
		else
			printf("%d: %s   ",i,memory[i]);

	}
	printf("\n");
 	clock++;
}

void END(int signum)
{
	printf("END of disk operation\n");
	exit(0);
}
