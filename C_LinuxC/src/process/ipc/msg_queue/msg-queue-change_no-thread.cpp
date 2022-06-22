#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/stat.h> //mkdir
#include <errno.h>
#include <string.h>
namespace ipc_msg_queue_change{

void msg_show_attr(int msg_id, struct msqid_ds msg_info)
{
	int ret = -1;
	sleep(1);
	ret = msgctl(msg_id, IPC_STAT, &msg_info);
	if( -1 == ret)
	{
		printf("获得消息信息失败\n");
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
		return ;		
	}
	
	printf("\n");
	printf("现在队列中的字节数：%d\n",msg_info.msg_cbytes);
	printf("队列中消息数：%d\n",msg_info.msg_qnum);
	printf("队列中最大字节数：%d\n",msg_info.msg_qbytes);
	printf("最后发送消息的进程pid：%d\n",msg_info.msg_lspid);
	printf("最后接收消息的进程pid：%d\n",msg_info.msg_lrpid);
	printf("最后发送消息的时间：%s",ctime(&(msg_info.msg_stime)));
	printf("最后接收消息的时间：%s",ctime(&(msg_info.msg_rtime)));
	printf("最后变化时间：%s",ctime(&(msg_info.msg_ctime)));
	printf("消息UID是：%d\n",msg_info.msg_perm.uid);
	printf("消息GID是：%d\n",msg_info.msg_perm.gid);
}

int main(int argc, char *argv[])
{
	int ret = -1;
	int msg_flags, msg_id;
	key_t key;
	struct msgmbuf{
		long mtype;
		char mtext[10];
		};	
	struct msqid_ds msg_info;
	struct msgmbuf msg_mbuf;
	
	int msg_sflags,msg_rflags;
	char *msgpath = "/tmp/ipc_msg/";

	system("rmdir /tmp/ipc_msg/");
//	system("mkdir /tmp/ipc_msg/");
	mkdir(msgpath,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);//<sys/stat.h>
	key = ftok(msgpath,'b');
	if(key != -1)
	{
		printf("成功建立KEY\n");
	}
	else
	{
		printf("建立KEY失败\n");
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
	}
	//使用ftok建立的key,已经存在必须用ipcrm -q 来删除
	//msg_flags = IPC_CREAT|IPC_EXCL;
	msg_flags = IPC_CREAT;
	msg_id = msgget(key, 0666 | msg_flags);//如果使用0x0666就没有读状态的权限, 一定要用0666,因为IPC_CREAT是0开头的八进制
	if( -1 == msg_id)
	{
		printf("消息建立失败\n");
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
		return 0;
	}	
	msg_show_attr(msg_id, msg_info);//用ftok 报Permission denied??
	
	msg_sflags = IPC_NOWAIT;
	msg_mbuf.mtype = 10;
	memcpy(msg_mbuf.mtext,"测试消息",sizeof("测试消息"));
	ret = msgsnd(msg_id, &msg_mbuf, sizeof("测试消息"), msg_sflags);//用IPC_NOWAIT 返回0
	if( -1 == ret)
	{
		printf("发送消息失败\n");
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
	}
	msg_show_attr(msg_id, msg_info);
	
	msg_rflags = IPC_NOWAIT|MSG_NOERROR;//消息太大,也不报错
	ret = msgrcv(msg_id, &msg_mbuf, 10,10,msg_rflags);
	if( -1 == ret)
	{
		printf("接收消息失败\n");
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
	}
	else
	{
		printf("接收消息成功，长度：%d\n",ret);
	}
	msg_show_attr(msg_id, msg_info);
	
	msg_info.msg_perm.uid = 8;
	msg_info.msg_perm.gid = 8;
	msg_info.msg_qbytes = 12345;
	ret = msgctl(msg_id, IPC_SET, &msg_info);
	if( -1 == ret)
	{
		printf("设置消息属性失败\n");
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
		return 0;		
	}
	msg_show_attr(msg_id, msg_info);//修改了uid就没有权限了
	
	ret = msgctl(msg_id, IPC_RMID,NULL);
	if(-1 == ret)
	{
		printf("删除消息失败\n");
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
		return 0;		
	}
	return 0;
}
}
