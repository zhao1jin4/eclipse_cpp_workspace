#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>

//fork 另开一个新的进程与原进程代码相同,相关打开文件描述符,进程堆栈等等都复制,锁子进程不继承,信号集为空
namespace fork_process
{

	int main(int argc, char* argv[])
	{
		pid_t pid; //进程ID  pid_t在sys/types中定义
		pid=fork();//返回进程ID,如果 是已经在子进程中调用fork返回0, 如果是父进程 调用fork 返回正数表示子进程ID,返回-1 失败
		char *msg;
		int n;
		int exit_code;
		switch(pid)
		{
			case -1:
				perror("FORK　FAILED");//输出错误
				exit(1);//0表示正常退出,非0表示,非正常退出
			case 0:
				msg="this is the child";
				n=5;
				exit_code=37;
				break;
			default:
				msg="this is the Parent";
				n=3;
				exit_code=0;
				break;
		}
		for (;n>0;n--)
		{
			puts(msg);//输出
			printf("当前进程 PID is %d\n",getpid());
			sleep(1);//切换进程,防止优先级高的一直执行下去
		}
		if(pid!=0) //父进程来执行
		{
			int stat_val;
			pid_t child_pid;
			child_pid=wait(&stat_val);//父进程来等侍子进程,状态信息存在stat_val里面
			printf("child has finished :PID=%d\n",child_pid);
			if(WIFEXITED(stat_val))//是否正常退出
				printf("child exited with code=%d",WEXITSTATUS(stat_val));//显示状态
			 else
				printf("child RUN ERROR EXIT");
		}
		exit(exit_code);
		//当子进程执行完成时,不会立即退出,父进程可以会从子进程读信息,(这个子进程是一个僵进程ps 显示<defunct>)
	}
}
