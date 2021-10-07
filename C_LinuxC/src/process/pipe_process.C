
	#include<sys/types.h>
	#include<unistd.h>
	#include<errno.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include <sys/wait.h>
namespace pipe_process
{

	//可打开两管道,实现双向
	int main(int argc, char* argv[])
	{
		 pid_t pid;
		int r_num;
		int pipe_fd[2];
		char buffer[100];
		memset(buffer,0,sizeof(buffer));

		 if(pipe(pipe_fd)<0)//建立一个管道,两个文件描述符,fildes[0]是用来读的文件描述符,而fildes[1]是用来写的文件描.返回 0 成功,-1失败,是在内存中的
		 {
			 perror("pipe error!");
			 //errno,的值EMFILE文件描述符已经在这个进程中打开 ,ENFILE 超过系统最大打开数
			 return -1;
		 }

		 if((pid=fork())==0)//子进程中,用来读
		 {
			 close(pipe_fd[1]);//关闭写
			 sleep(2);
			 if((r_num=read(pipe_fd[0],buffer,100))>0)
				printf("%d number read from pipe is %s\n",r_num,buffer);
			 printf("chihld PID is %d\n",getpid());
			 close(pipe_fd[0]);//关闭读
			 exit(0);
		 }else if(pid>0)
		 {
			 close(pipe_fd[0]);

			 if(write(pipe_fd[1],"hello",5)!=-1)
				printf("parent wirte success\n");
			 if(write(pipe_fd[1],"Pipe",5)!=-1)
				printf("parent wirte success\n");
			 printf("parent PID is %d\n",getpid());
			 close(pipe_fd[1]);
			 sleep(3);
			 waitpid(pid,NULL,0);//等待进程
			 exit(0);
		 }




	}
}
