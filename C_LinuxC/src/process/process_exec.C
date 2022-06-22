#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#include<errno.h>
#include<string.h>
namespace exec_process
{

	void testExeclp()
	{
		//函数名l=link ,v=vector,e=enviroment,p=path ,表示参数
		//其它函数 execl,execv,execle,execve,execlp,execvp,execvpe ,出错返回-1,设置 errno
		//这些函数是进入指定进程，后面的代码不会被执行,如果想等执行完再执行后面的代码使用system函数
		if(execlp("ps","ps","-ef",0)<0)// 到PATH中找ps,要替代新的进程,没有建立新进程,ID号相同 ,后面的代码不会执行
		{
			perror("execlp error !");
		}

		printf("这的代码不会被执行.\n");
	}
	void testExecle()
	{
		//const放*后 是常指针,不要改变指向
		//const放*前 是指针指向常对象,不可改变我指向的值

		char *const envp[]={"PATH=/tmp","USER=david",NULL};//必须以NULL结尾
		if(execle("/usr/bin/env", "env", "--help",NULL, envp) == -1 )//参数也一定是以NULL结束
//		if(execle("/usr/bin/env", "env", NULL, envp) == -1 )//第二个参数env是argv[0],进程名不能为空
		{
			perror("Execle error\n");
			printf("error reason: %s \n",strerror(errno));// Invalid argument
		}
		printf("这的代码不会被执行.\n");
	}

	int test_system()
	{
	    printf("Running ps with system\n");
	    system("ps -ax");//stdlib.h中的
	    printf("Done.\n");
	}

	int main(int argc, char* argv[])
	{
		printf("before exec  \n");

		//test_system();
		//testExeclp();//后面的代码不会执行
		testExecle();//error


		printf("after exec  \n");
		return 1;
	}
}
