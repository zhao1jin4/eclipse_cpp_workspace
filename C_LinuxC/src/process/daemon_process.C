#include<sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syslog.h>

namespace daemon_process
{

	int main(int argc, char* argv[])
	{
		//cygwin 下没有/var/log/message
		openlog("daemon_process",LOG_PID,LOG_DAEMON);//是文件/var/log/message
		//LOG_DAEMON是来自守护进程的消息,LOG_PID 每个消息包含进程PID


		pid_t pc,sid;
		int i,fd,len;
		char * buf="this is a Deamon \n";
		len=strlen(buf);
		pc=fork();
		if(pc<0)
		{
			syslog(LOG_ERR,"fork error !\n");
			exit(-1);
		}else if (pc>0)
			exit(0);


		//只在子进程中
		if((sid=setsid()<0))//建立一个新会话(session),成为一新进程组的首进程,脱离终端
			syslog(LOG_ERR,"setsid error !\n");
		chdir("/"); //修改当前目录为 /
		umask(0);//子进程重新设置(继承父进程的)

		for(i=0;i<FOPEN_MAX;i++)//子进程关闭文件描述符(继承父进程的)
			close(i);

		syslog(LOG_INFO,"start work!\n");
		closelog();

		//守护进程的工作
		while(1)
		{
			if((fd=open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0600)<0))//0600文件权限,open函数操作文件,基于非缓存的方式
			{
				perror("open error !");
				exit(-1);
			}
			write(fd,buf,len+1);
			close(fd);
			sleep(5);
		}

		// /tmp/  cygwin 下可以运行
	}
}
