#include <sys/types.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include<errno.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include <sys/wait.h>

namespace fifo_read
{


	const char * FIFO ="/tmp/myfifo";//使用C:/ 打开报错
	int main(int argc, char* argv[])
	{
		char buffer[100];
		int fd;
		int nread;
		if((mkfifo(FIFO,O_CREAT|O_EXCL)<0)&& (errno!=EEXIST))//open函数的选项 ,O_EXEC：如果使用了O_CREAT 而且文件已经存在,就会发生一个错误.
			printf("can not create fifoserver\n");
		printf("preparing for reading bytes...\n");
		memset(buffer,0,sizeof(buffer));
		fd=open(FIFO,O_RDONLY|O_NONBLOCK,0);
		if(fd==-1)
		{
			printf("open error!,%d", errno);//13==EACCES
			exit(1);
		}
		while(1)
		{
			memset(buffer,0,sizeof(buffer));
			if((nread=read(fd,buffer,100))==-1)
			{
				if(errno==EAGAIN)
					printf("no data yet\n");
			}
			printf("read %s form FIFO \n",buffer);
			sleep(1);
		}
		pause();
		unlink(FIFO);

		return 1;
	}
}
