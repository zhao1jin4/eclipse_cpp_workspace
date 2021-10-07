#include<sys/types.h>
	#include<unistd.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include <sys/wait.h>
	#include <signal.h>
namespace signal_process
{

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
			raise(SIGSTOP);
			exit(0);
		}else
		{
			printf("pid=%d\n",pid);
			if((waitpid(pid,NULL,WNOHANG))==0)
			{
				if((ret=kill(pid,SIGKILL))==0)
					printf("kill %d\n",pid);
				else
					perror("kill");
			}
		}
	}
}
