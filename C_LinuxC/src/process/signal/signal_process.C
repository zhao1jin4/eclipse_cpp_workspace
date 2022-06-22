#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <signal.h>

namespace signal_process
{
	//信号是某种错误产生
	int main(int argc, char* argv[])
	{
		pid_t pid;
		int ret;
		if((pid=fork())<0)
		{
			perror("fork error!");
			exit(1);
		}
		if(pid==0)
		{
			raise(SIGSTOP);//raise
			exit(0);
		}else
		{
			printf("pid=%d\n",pid);
			if((waitpid(pid,NULL,WNOHANG))==0)//wait no hang(悬挂)如果子线程没有完成返回0，不等待继续执行
			{
				if((ret=kill(pid,SIGKILL))==0)//kill.如权限不足errno=EPERM,不存在errno=ESRCH
					printf("kill %d\n",pid);
				else
					perror("kill");
			}
		}
	}
}
