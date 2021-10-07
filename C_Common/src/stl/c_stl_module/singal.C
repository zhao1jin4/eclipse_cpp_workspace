
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

namespace stl_signal
{

	char tmpfilename [L_tmpnam];
	void terminate (int param)
	{
		if(SIGINT==param)
			printf ("Get Signal NO:%d\n",param);

		printf ("Terminating program...\n");
		remove (tmpfilename);
		exit(1);
	}
	void  signalTest()
	{
		//------ signal.h
		void (*prev_fn)(int);
		prev_fn = signal (SIGINT,terminate);//注册发到信号时的处理函数，函数声明头 void xxx(int param)
		if(prev_fn== SIG_ERR)
		{
			printf("errno:%d",errno );
		}
		if (prev_fn==SIG_IGN)
			signal (SIGTERM,SIG_IGN);
		tmpnam (tmpfilename);
		raise(SIGINT);//发出信号，MinGW ,VC测试 OK
	}

	int main(int argc,char* argv[] )
	{
		signalTest();
		return 1;
	}

}
