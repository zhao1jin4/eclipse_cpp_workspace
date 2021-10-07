#include<unistd.h>
#include<stdio.h>


namespace exec_process
{

	void testExeclp()
	{
		//函数名l=link ,v=vector,e=enviroment,p=path ,表示参数
		//其它函数 execl,execv,execle,execve,execlp,execvp ,出错返回-1,设置 errno
		if(execlp("ps","ps","-ef",0)<0)// 到PATH中找ps,要替代新的进程,没有建立新进程,ID号相同 ,后面的代码不会执行
			perror("execlp error !");
	}
	void testExecle()
	{
		char *envp[]={"PATH=/home/temp/bin","USER=zh"};
		if(execle("/usr/bin/env","env",NULL,envp)<0)//自己设置环境变量
			perror("execle error !");
	}

	int main(int argc, char* argv[])
	{
		printf("before exec  \n");

		//testExeclp();
		testExecle();

		printf("after exec  \n");
		return 1;
	}
}
