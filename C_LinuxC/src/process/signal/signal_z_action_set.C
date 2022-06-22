
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

namespace signal_set
{
	int print_type;
	void single_func (int param)
	{
		printf("in single_func,NO:%d\n",param);
		if(SIGQUIT==param)
		{
			print_type=11; //在信号处理函数中使用printf 不安全
		}
		if(SIGINT==param)
		{
			print_type=3;
		}
	}
	void (*prev_fn)(int);

	int main(int argc, char* argv[])
	{
		sigset_t set,pendset;
		struct sigaction action1,action2;
		if(sigemptyset(&set)<0)//初始化为空,sigfillset()初始化为指定的信号
			perror("sigemptyset error !");
		if(sigaddset(&set,SIGQUIT)<0)
			perror("sigaddset SIGQUIT error !");
		if(sigaddset(&set,SIGINT)<0)
			perror("sigaddset SIGINT error !");



		//SIG_BLOCK把set中的信号"增加"到信号屏蔽字中,SIG_UNBLOCK(删除),SIG_SETMASK(设置,即可替换已有的)
		if(sigprocmask(SIG_BLOCK,&set,NULL)<0)//像action.sa_mask.最后一个参数输出已经有的
			perror("sigprocmask error !");
		else
		{
			printf("blocked \n");
			sleep(5);//等待时按 ctrl+c 会默认处理 ,退出
		}

		if(sigprocmask(SIG_UNBLOCK,&set,NULL)<0)//删除
			perror("sigpromask error !");
		else
			printf("unblock \n");

		//------------上 信号集


		if(sigismember(&set,SIGINT))//是否set里有
		{
			printf("receive SIGINT \n");
			sigemptyset(&action1.sa_mask);//sa_mask 里的信号不对传递给进程,可以防止信号处理函数没有处理完成又来信号

			//action1.sa_flags=SA_RESETHAND;//表示第二次调用signal()重置到SIG_DFL (reset hand),即只使用一次
			action1.sa_flags=SA_RESTART;//默认情况下SIGINT 指定的函数只处理一次,下次再收到相同信号就是默认处理,加上SA_RESTART一直是指定的函数处理

			action1.sa_handler=single_func;//sa=sigaction
			sigaction(SIGINT,&action1,NULL);//替代signal(),最后一个参数可输出原来的处理函数
		}

		if(sigismember(&set,SIGQUIT))//按 ctrl+\ 产生(eclipse结束进程按钮) SIGQUIT信号,提示产生core 文件
		{
			printf("receive SIGQUIT \n");
			sigemptyset(&action2.sa_mask);
			action2.sa_handler=single_func; //SIG_DFL
			sigaction(SIGTERM,&action2,NULL);
		}
		while(true){
			printf("runing  \n");
			sleep(1);
		}
		//sigsuspend(&pendset);//将被阻塞未处理的信号输出.也像pause();挂起直到信号集中一个信号到达
		if(print_type==11)
		{
			printf ("SIGQUIT down\n");
		}else if(print_type==3){
			printf ("you pressed control + c \n");
		}

	}
}
