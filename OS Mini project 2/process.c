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
void IncClock(int signum);
void END(int signum);
struct msgbuff message;
pid_t pid;
key_t up;
key_t down;
int clock=0;

int main()
{
	signal (SIGUSR2, IncClock);
	signal (SIGINT, END);
	up = msgget(666, IPC_CREAT|0644);
	down = msgget(555, IPC_CREAT|0644);
	printf("Enter the name of the file\n");
	char file[100];
	scanf("%s",file);
	//file="input.txt";

	FILE * fp;
	fp = fopen(file, "r"); 
	if (fp == NULL) 
	{   
		printf("no file with this name \n"); 
		exit(0); 
	}
	int start=0,send_val,rec_val,end;
	char oper[3],msg[64];
	message.mtype=getpid();
	strcpy(message.mtext,"EE");
	send_val = msgsnd(up, &message, sizeof(message.mtext), !IPC_NOWAIT);
	while(1)
	{
		if(fscanf(fp,"%d",&start)!=1)
			break;
		fscanf(fp,"%s",oper);
		fscanf(fp,"%s",msg);
		while(start>clock)	{}
		if(oper[0]=='A')
		{
			strcpy(message.mtext,"A");
			end=clock+3;
		}

		else if (oper[0]=='D')
		{
			strcpy(message.mtext,"D");
			end=clock+1;
		}

		else
		{
			perror("input Error");
			exit(0);
		}
		strcat(message.mtext,msg);
		printf("this is the string before send: %s\n",message.mtext);
		message.mtype=getpid();
		send_val = msgsnd(up, &message, sizeof(message.mtext), !IPC_NOWAIT);
	  
	  	if(send_val == -1)
	  		perror("Error in send");
		rec_val = msgrcv(down, &message, sizeof(message.mtext), getpid(), !IPC_NOWAIT);
		while(rec_val==-1)
			rec_val = msgrcv(down, &message, sizeof(message.mtext), getpid(), !IPC_NOWAIT);
		if(message.mtext[0]=='0')
		  printf("successful ADD\n");
		else if(message.mtext[0]=='1')
		  printf("successful DEL\n");
		else if(message.mtext[0]=='2')
		  printf("unable to ADD\n");
		else if(message.mtext[0]=='3')
		  printf(" unable to DEL\n");
		else
			printf("recived: %s\n",message.mtext);
	}
	printf("End of process \n");
	fclose(fp);
	return 0;
}
	
void IncClock(int signum)
{
	printf("clock increament by 1\n");
 	clock++;
}

void END(int signum)
{
	printf("END of process\n");
	exit(0);
}
