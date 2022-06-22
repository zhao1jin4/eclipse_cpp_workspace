#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <time.h>
//#include <linux/msg.h>//不能引入,报重复定义

namespace ipc_msg_queue{

void printTime(time_t rawtime){//time.h
	tm* timeinfo = localtime ( &rawtime );//转为当地时间,可以读年月日等
	char buffer [80];
	strftime (buffer,80,"%Y-%m-%d %H:%M:%S %Z",timeinfo);//把日期转字串,%Y-%m-%d %H:%M:%S  ,%X表示%H:%M:%S ,%Z 为CST或China Standard Time
	printf ("%s\n",buffer);
}
void printMsgQueueStat(int msgid){
	msqid_ds stat;
	msgctl(msgid, IPC_STAT, &stat);
	printf("message queue perm info : uid=%d,gid=%d,cuid=%d,cgid=%d,mode=%d\n", stat.msg_perm.uid, stat.msg_perm.gid, stat.msg_perm.cuid, stat.msg_perm.cgid, stat.msg_perm.mode);
	printf("number of messages currently on queue:%d\n",stat.msg_qnum);
	printf("max number of bytes allowed on queue:%d\n",stat.msg_qbytes);
	printf("pid of last msgsnd():%d\n",stat.msg_lspid);
	printf("pid of last msgrcv():%d\n",stat.msg_lrpid);

	printf("time of last msgsnd:");
	printTime(stat.msg_stime);

	printf("time of last msgsnd:");
	printTime(stat.msg_rtime);

	printf("time of last change:");
	printTime(stat.msg_ctime);
}


int receiver()
{
	struct my_msg_st {
	    long int my_msg_type;//第一个必须是 long int类型,和long类型相同长度8
	    char some_text[BUFSIZ];
	};

    int running = 1;
    int msgid;
    struct my_msg_st some_data;
    long int msg_to_receive = 0;

/* First, we set up the message queue. */

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

/* Then the messages are retrieved from the queue, until an end message is encountered.
 Lastly, the message queue is deleted. */

    while(running) {
    	//man msgrcv 有消息格式
        if (msgrcv(msgid, (void *)&some_data, BUFSIZ,//长度不能包括结体的第一个long int,和long类型相同长度8
                   msg_to_receive, 0) == -1)//msgtyp : =0 只接收第一个可用的,>0是表示与(结体的第一个long)相同的第一个消息  ,<0 时表示比(结体的第一个long)小的第一个消息
                		   //如最后一个参数有IPC_NOWAIT,没有消息时不会阻塞返回失败
        {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("You wrote: %s", some_data.some_text);
        if (strncmp(some_data.some_text, "end", 3) == 0) {
            running = 0;
        }
    }

    printMsgQueueStat(msgid);

    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
void sender(){

	#define MAX_TEXT 512
	struct my_msg_st {
		long int my_msg_type;
		char some_text[MAX_TEXT];
	};

	 int running = 1;
	struct my_msg_st some_data;
	int msgid;
	char buffer[BUFSIZ];

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	printMsgQueueStat(msgid);
	while(running) {
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		some_data.my_msg_type = 1;
		strcpy(some_data.some_text, buffer);

		//长度不能包括结体的第一个long int
		if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {//如最后一个参数有IPC_NOWAIT,队列满时不会阻塞返回失败
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
		if (strncmp(buffer, "end", 3) == 0) {
			running = 0;
		}
	}

	exit(EXIT_SUCCESS);
}

/*
 ipcs

 ipcrm -q 0
-Q, --queue-key
 -q, --queue-id
 */
int main(int argc, char *argv[])
{
	printf("same:%d,long int=%d,long=%d",sizeof(long int)==sizeof(long),sizeof(long int),sizeof(long));


	//和semaphore 函数形式一样的
	//MSGMAX 是消息最大长度, MSGMNB 队列最大长度 定义在 <linux/msg.h>文件中,不能引入,报重复定义
	if(argc>1)
	{
		printf("----receiver...\n");
		receiver();
	}
	else
	{
		printf("----sender...\n");
		sender();
	}
}


}
