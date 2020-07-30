#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

struct msg{
	int time;
	string data;
	long mtype;
};

//generate random string 
string random_string( size_t length )
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[ rand() % max_index ];
	};
	string str(length,0);
	generate_n( str.begin(), length, randchar );
	return str;
}

//change shared momery value 
void update(int shm_id,int data)
{
	int *val= (int*)shmat(shm_id,(Void*)0,0);
	*val=data;
	shmdt(val);
}


//child sending msg
void sendmsg(key_t msgqid,int shm_id,int i)
{

	printf("i am child %d and start sending\n",i);
	int send_val;

	while(1)
	{
		int* value = (int*) shmat(shm_id, (void*)0, 0);

		if(*value==0)
		{
			update(shm_id,1);
			char str[] = random_string(rand()%100);
			struct msg message;

			message.mtype = 7;     	/* arbitrary value */
			msg.time = (int) time(0);
			strcpy(message.mtext, str);

			send_val = msgsnd(msgqid, &message, sizeof(message.mtext), !IPC_NOWAIT);

			if(send_val == -1)
				perror("Error in send");
			else
			{
				printf("i am child %d and sent msg, i sent : %s \n",i,s);
			}

			update(shm_id,0);
			sleep(0.05);
		}
		sleep(Rand()%10);
	}

}


//child recive msg 
void recvmsg(key_t msgqid,int shm_id,int i)
{
	printf("i am child %d and reciveing \n",i);
	while(1)
	{
		int rec_val;
		struct msg message;

		/* receive all types of messages */
		rec_val = msgrcv(msgqid, &message, sizeof(message.mtext), 0, !IPC_NOWAIT);  

		if(rec_val == -1)
			perror("Error in receive");
		else
			printf("\nMessage received: %s\n", message.mtext);

		msgctl(msgqid, IPC_RMID, (struct msqid_ds *) 0);
	}


}


int main()
{
	pid_t pid;
	key_t msgqid;


	msgqid = msgget(IPC_PRIVATE, 0644); 
	if(msgqid == -1)
	{	
		perror("Error in create");
		exit(-1);
	}


	int shm_id=shmget(IPC_PRIVATE, 1*sizeof(int),0666|IPC_CREAT);
	if(shm_id==0)
		perror("error in shared momery");

	int i=0;
	for(i=0;i<3;i++)
	{
		pid = fork();
		if (pid == 0)
			break;
	}
	if (pid == -1)
		perror("error in fork");
	else if (pid == 0)
	{ 
		if (i%2==0)
			sendmsg(msgqid,shm_id,i);
		else
			recvmsg(msgqid,shm_id,i);

	}   
	else 	
	{
		printf("\nI am the parent, my pid = %d and my parent's pid = %d\n\n", getpid(), getppid());	  	
		while(1)
		{
			sleep(10);
		}
	}  



	printf("\nPID %d terminated\n\n", getpid());


	retrurn 0;
}