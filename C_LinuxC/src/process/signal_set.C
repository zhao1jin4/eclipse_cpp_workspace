
	#include<sys/types.h>
	#include<unistd.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include <sys/wait.h>
	#include <signal.h>
	#include <errno.h>

namespace signal_set
{
	void single_func (int param)
	{
		printf("in single_func,NO:%d",param);
	}
	void (*prev_fn)(int);

	int main(int argc, char* argv[])
	{
		sigset_t set,pendset;
		struct sigaction action1,action2;
		if(sigemptyset(&set)<0)//初始化为空
			perror("sigemptyset error !");
		if(sigaddset(&set,SIGQUIT)<0)
			perror("sigaddset SIGQUIT error !");
		if(sigaddset(&set,SIGINT)<0)
			perror("sigaddset SIGINT error !");

		if(sigprocmask(SIG_BLOCK,&set,NULL)<0)//当发生信号时,把它放在信号集中,并集
			perror("sigprocmask error !");
		else
		{
			printf("blocked \n");
			sleep(5);//等待时按 ctrl+c 会默认处理 ,退出
		}

		if(sigprocmask(SIG_UNBLOCK,&set,NULL)<0)//交集
			perror("sigpromask error !");
		else
			printf("unblock \n");

		while(1)
		{
			if(sigismember(&set,SIGINT))
			{
				//printf("receive SIGINT \n");
				sigemptyset(&action1.sa_mask);
				action1.sa_handler=single_func;
				sigaction(SIGINT,&action1,NULL);
			}else if(sigismember(&set,SIGQUIT))
			{
				printf("receive SIGQUIT \n");
				sigemptyset(&action2.sa_mask);
				action2.sa_handler=single_func; //SIG_DFL
				sigaction(SIGTERM,&action2,NULL);
			}
			sleep(0.5);
		}
		//ctrl + \ 会退出程序
		//linux 下测试可能效果不一样
	}
}
