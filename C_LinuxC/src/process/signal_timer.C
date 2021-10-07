
	#include<sys/types.h>
	#include<unistd.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include <sys/wait.h>
	#include <signal.h>
	#include <errno.h>

namespace signal_timer
{

	void single_func (int param)
	{
		if(SIGALRM==param)
			printf ("timer down,Get Signal NO:%d\n",param);
		if(SIGINT==param)//在eclipse中无效,要在cygwin中
			printf ("you pressed control + c.,NO:%d",param);
	}
	void (*prev_fn)(int);

	int main(int argc, char* argv[])
	{
		int ret;
		ret=alarm(5);//时间到了后会发出SIGALRM信号,如参数为0取消以前的定时器,每个进程只能有一个定时器

		prev_fn = signal (SIGALRM,single_func);//注册发到信号时的处理函数，函数声明头 void xxx(int param)
		//处理函数如是 SIG_DFL,表示使用默认,SIG_IGN表示忽略
		if(prev_fn== SIG_ERR)
			printf("errno: %d", errno );

		prev_fn = signal (SIGINT,single_func);
		if(prev_fn== SIG_ERR)
			printf("errno: %d", errno );

		printf("wait 5 sends,can press ctrl+c \n");
		fflush(stdout);
		pause();
		printf("%d",ret);

		//STL库中有singal 函数,处理收到的信息
	}
}
