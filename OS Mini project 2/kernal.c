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

void END(int signum);
void IncClock(int signum);
struct msgbuff message;
pid_t pid;
key_t upD;
key_t downD;
key_t upP;
key_t downP;
int clock=0;
long ID[1000];
int last=0;
int from[1000];
char req[1000][65];
char Kres[1000][2];
char Dres[1000][2];
int curr=0;


int addtolist(long type)
{
	int i=0;
	for(i=0;i<last;i++)
	{
		if(ID[i]==type)
			return i;
	}
	ID[last]=type;
	last+=1;
	return last-1;
}



int main()
{
	signal (SIGALRM, IncClock);
	signal (SIGINT, END);
	upD = msgget(888, IPC_CREAT|0644);
	downD = msgget(777, IPC_CREAT|0644);
	upP = msgget(666, IPC_CREAT|0644);
	downP = msgget(555, IPC_CREAT|0644);
	int send_val=-1;
	int rec_val=-1;
	rec_val = msgrcv(upD, &message, sizeof(message.mtext), 0, !IPC_NOWAIT);    
	addtolist(message.mtype);
	while(1)
	{
		alarm(1);
		rec_val = msgrcv(upP, &message, sizeof(message.mtext), 0, !IPC_NOWAIT);
		if(rec_val != -1)
		{
			printf("recived %s from process\n", message.mtext);
			char res[2],temp[64];
			strcpy(temp,message.mtext);
			strcpy(req[curr],temp);
			int rec=addtolist(message.mtype);
			kill(ID[0], SIGUSR1);
			rec_val = msgrcv(upD, &message, sizeof(message.mtext),ID[0], !IPC_NOWAIT);
			if(rec_val==-1)
				printf("can't get count\n");
			int cnt=(message.mtext[0]);
			printf("count=%d\n",cnt);
			if(temp[0]=='A')
			{
				if(cnt>0)
				{
					message.mtype=ID[rec];
					strcpy(Kres[curr],"0");
					strcpy(message.mtext,temp);
					send_val = msgsnd(downD, &message, sizeof(message.mtext), !IPC_NOWAIT);
					if(send_val == -1)
						printf("Error in send to disk\n");
					else
						printf("send to disk\n");
					rec_val = msgrcv(upD, &message, sizeof(message.mtext), 0, !IPC_NOWAIT);    
					while(rec_val==-1)
					{
						alarm(1);
						rec_val = msgrcv(upD, &message, sizeof(message.mtext), 0, !IPC_NOWAIT); 	
					}
					printf("recive from disk\n");
					strcpy(res,message.mtext);
					strcpy(Dres[curr],res);				
				}
				else
				{
					strcpy(res,"2");
					strcpy(Kres[curr],"2");
					strcpy(Dres[curr],"6");
				}
			}
			else if (temp[0]=='D')
			{
				if(cnt==10)
				{
					strcpy(res,"3");
					strcpy(Kres[curr],"2");
					strcpy(Dres[curr],"6");
				}
				else
				{
					message.mtype=ID[rec];
					strcpy(Kres[curr],"5");
					strcpy(message.mtext,temp);
					send_val = msgsnd(downD, &message, sizeof(message.mtext), !IPC_NOWAIT);
					if(send_val == -1)
						printf("Error in send to disk\n");
					else
						printf("send to disk\n");
					rec_val = msgrcv(upD, &message, sizeof(message.mtext), 0, !IPC_NOWAIT);    
					while(rec_val==-1)
					{
						alarm(1);
						rec_val = msgrcv(upD, &message, sizeof(message.mtext), 0, !IPC_NOWAIT); 	
					}
					printf("recive from disk\n");
					strcpy(res,message.mtext);
					strcpy(Dres[curr],res);	
				}
			}
			else
			{
				printf("garbag: %s\n",message.mtext);
				continue;
			}
				
			strcpy(message.mtext,res);
			from[curr]=message.mtype=ID[rec];
			send_val = msgsnd(downP, &message, sizeof(message.mtext), !IPC_NOWAIT);
		  	if(send_val == -1)
		  		printf("Error in send to process\n");
			else
				printf("Massage has been sent %s\n",message.mtext);
			curr+=1;
		}
	}	
  	return 0;
}

void END(int signum)
{
	printf("End of kernal\n");

	FILE * fp;
	fp = fopen("output.txt", "w"); 
	int i=0;
	for(i=0;i<curr;i++)
	{
		fprintf(fp,"from %d req: %s Kres: %s Dres: %s \n",from[i],req[i],Kres[i],Dres[i]);
	}
	fclose(fp);
	i=0;
	for(i=0;i<last;i++)
	{
		kill(ID[i],SIGINT);
	}
	msgctl(upD, IPC_RMID, (struct msqid_ds *) 0);
	msgctl(downD, IPC_RMID, (struct msqid_ds *) 0);
	msgctl(upP, IPC_RMID, (struct msqid_ds *) 0);
	msgctl(downP, IPC_RMID, (struct msqid_ds *) 0);
	exit(0);
  
}

void IncClock(int signum)
{
	printf("clock increament by 1\n");
	clock++;
	int i=0;

	for(i=0;i<last;i++)
	{
		kill(ID[i],SIGUSR2);
	}
}
