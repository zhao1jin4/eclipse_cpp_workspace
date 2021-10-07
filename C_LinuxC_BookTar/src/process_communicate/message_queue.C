	#include<sys/types.h>
	#include<unistd.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <string.h>
	#include <sys/msg.h>
namespace message_queue
{


	//ipcs 要在linux下使用
	int main(int argc, char* argv[])
	{
		const int BUFFER_SIZE=512;
		struct mymsg {
			long int    mtype;       /* message type */
			char        mtext[BUFFER_SIZE];    /* message text */
		};

		int qid;
		key_t key;
		int len;
		struct mymsg msg;
		if((key=ftok(".",'a'))==-1)
		{
			perror("ftok error !\n");
			exit(-1);
		}
		if((qid=msgget(key,IPC_CREAT|0666))==-1)//不能在cygwin中运行
		{
			perror("msgget error !\n");
			exit(-1);
		}
		printf("opend queue %d\n",qid);
		puts("please ener the mesasge to queue:");
		if((fgets((&msg)->mtext,BUFFER_SIZE,stdin))==NULL)
		{
			perror("fget error !\n");
			exit(-1);
		}
		msg.mtype=getpid();
		len=strlen(msg.mtext);
		if((msgsnd(qid,&msg,len,0))<0)
		{
			perror("msgsnd error !\n");
			exit(-1);
		}
		if(msgrcv(qid,&msg,BUFFER_SIZE,0,0)<0)
		{
			perror("msgrcv error !\n");
			exit(-1);
		}
		printf("message is  %d\n",(&msg)->mtext);
		if((msgctl(qid,IPC_RMID,NULL))<0)
		{
			perror("msgctl error !\n");
			exit(-1);
		}
	}
}
