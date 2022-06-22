
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

namespace signal_timer
{
	int print_type;
	void single_func (int param)
	{
		if(SIGALRM==param)
		{
			print_type=2;
			printf ("timer down,Get Signal NO:%d\n",param);//在信号处理函数中使用printf 不安全
		}
		if(SIGINT==param)//control+C 产生SIGINT
		{
			print_type=3;
			printf ("you pressed control + c.,NO:%d \n",param);
		}
	}
	void (*prev_fn)(int);

	int main(int argc, char* argv[])
	{
		int ret;
		ret=alarm(5);//时间到了后会发出SIGALRM信号,如参数为0取消以前的定时器,每个进程只能有一个定时器
		printf("%d\n",ret);

		//linux 版本建立用 sigaction 替代老的  signal
		prev_fn = signal (SIGALRM,single_func);//注册发到信号时的处理函数，函数声明头 void xxx(int param)
		//处理函数如是 SIG_DFL,表示使用默认(default),SIG_IGN表示忽略(ignore)
		if(prev_fn== SIG_ERR)
			printf("errno: %d", errno );

		prev_fn = signal (SIGINT,single_func);
		if(prev_fn== SIG_ERR)
			printf("errno: %d", errno );

		printf("wait 5 sends,can press ctrl+c \n");
		fflush(stdout);
		pause();//挂起,直到捕捉到一个信号
		if(print_type==2)
		{
			printf ("alarm timer down\n");
		}else{
			printf ("you pressed control + c \n");
		}
		//STL库中有singal 函数,处理收到的信息
	}
}
