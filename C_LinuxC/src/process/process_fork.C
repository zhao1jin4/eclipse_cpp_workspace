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
			printf("当前进程 PID is %d\n",getpid());// getppid() 可以得到父进进程的ID
			sleep(1);//切换进程,防止优先级高的一直执行下去
		}
		if(pid!=0) //父进程来执行
		{
			int stat_val;
			pid_t child_pid;
			child_pid=wait(&stat_val);//父进程来等侍子进程,状态信息存在stat_val里面

			//waitpid(pid,&stat_val,WNOHANG);//指定子进程PID(如参数是-1返回任意一个子进程和wait一样)
			//WNOHANG不阻塞等待,如线程没有结束,也不等,用于检查子进程是否执行完成,如子进程运行返回0,结束返回子进程pid,失败返回-1设置errno
			//失败包括没有子进程ECHILD,被信号中断EINTR,EINVAL无效参数


			printf("child has finished :PID=%d\n",child_pid);
			if(WIFEXITED(stat_val))//是否正常退出
				printf("child exited with code=%d",WEXITSTATUS(stat_val));//退出码,这里是37
			 else
				printf("child RUN ERROR EXIT");
			/*还有
			   if(WIFSIGNALED(status))//因一个未捕获的信号退出返回非0值
					WTERMSIG(status) //如果WIFSIGNALED返回非0,这个返回信号代码
				if(WIFSTOPPED(status))//如意外中止返回非0值
					WSTOPSIG(status) //如果WIFSTOPPED返回非0,这个返回信号代码
			*/
		}
		exit(exit_code);
		//当子进程执行完成时,不会立即退出,父进程可以会从子进程读信息,(这个子进程是一个僵进程ps al 显示<defunct>)
	}
}
