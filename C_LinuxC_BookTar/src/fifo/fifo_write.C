
	#include <sys/types.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include<errno.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include <sys/wait.h>

namespace fifo_write
{

	const char * FIFO_SERVER ="/tmp/myfifo"; //使用C:/ 打开报错
	int main(int argc, char* argv[])
	{
		char buffer[100];
		int fd;
		int nwrite;
		fd=open(FIFO_SERVER,O_WRONLY|O_NONBLOCK,0);
		if(fd==-1)
		{
			perror("open error !");
			exit(1);
		}

		strcpy(buffer,"hello world");
		if((nwrite=write(fd,buffer,100))==-1)
		{
			if(errno==EAGAIN)
				printf("FIFO has not bead read yet,try later\n");
		}else
			printf("write %s to FIFO \n",buffer);

		return 1;
	}
}
