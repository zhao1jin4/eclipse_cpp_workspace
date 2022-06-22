#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>

namespace file_control
{

//没啥用
void setFlag(){

	int flags = -1;
	char buf[] = "FCNTL";

	int fd = open("/tmp/test.txt", O_RDWR);
	/*获得文件状态*/
	flags = fcntl(fd, F_GETFL, 0);//FL=flag
	/*增加状态为可追加*/
	flags |= O_APPEND;
	/*将状态写入*/
	//文档说可以修改O_APPEND, O_ASYNC,  O_DIRECT,  O_NOATIME,  and  O_NONBLOCK
	flags = fcntl(fd, F_SETFL, &flags);//失败？不能增加 O_APPEND
	if( flags < 0 ){
		char * reason=strerror(errno);//errno.h,string.h
		fprintf(stderr,"error! %s\n",reason);
		return ;
	}
	/*向文件中写入字符串*/
	write(fd, buf, strlen(buf));
	close(fd);

}
int main(int argc, char *argv[])
{
	{
		int flags = -1;
		int accmode = -1;
		/*获得标准输入的状态的状态*/
		flags = fcntl(0, F_GETFL, 0);
	  if( flags < 0 ){
		/*错误发生*/
		printf("failure to use fcntl\n");
		return -1;
	  }
	  /*获得访问模式*/
	  accmode = flags & O_ACCMODE;
	  if(accmode == O_RDONLY)/*只读*/
		printf("STDIN READ ONLY\n");
	  else if(accmode == O_WRONLY)/*只写*/
		printf("STDIN WRITE ONLY\n");
	  else if(accmode ==O_RDWR)/*可读写*/
		printf("STDIN READ WRITE\n");
	  else/*其他模式*/
		printf("STDIN UNKNOWN MODE");

	  if( flags & O_APPEND )
		printf("STDIN APPEND\n");
	  if( flags & O_NONBLOCK )
		printf("STDIN NONBLOCK\n");

	}
	setFlag();

	{
		int uid;
		/*打开文件test.txt*/
		int fd = open("/tmp/test.txt", O_RDWR);

		fcntl(fd, F_SETOWN,1000); //还有　F_DUPFD 复制文件描述符，功能和dup，dup2函数功能一样

		//int dup(int fd); //返回新的描述符和已经有描述符指向同一文件(通道),新的总是可用的最小值
		//int dup2(int oldfd,int newfd);  //如果newfd，前面已经打,先自动关闭.再从old复制到newfd.

		/*获得接收信号的进程ID*/
		uid = fcntl(fd, F_GETOWN);
		printf("the SIG recv ID is %d\n",uid);

	  close(fd);
	}
	return 0;
}

}


