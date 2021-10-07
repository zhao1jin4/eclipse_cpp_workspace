#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>


namespace file_select
{

	 int main(int argc, char *argv[])
	 {
		 int fds[2];
		 char buf[7];
		 int i,rc,maxfd;
		 fd_set inset1,inset2;
		 struct timeval tv;
		 if((fds[0]=open("c:/temp/hello1",O_RDWR|O_CREAT,0666))<0)
			 perror("open hello1 error !");
		 if((fds[1]=open("c:/temp/hello2",O_RDWR|O_CREAT,0666))<0)
			 perror("open hello2 error !");
		 if((rc=write(fds[0],"hello!\n",7)))
		 	printf("rc=%d\n",rc);
		 lseek(fds[0],0,SEEK_SET);
		 maxfd=fds[0]>fds[1]?fds[0]:fds[1];
		 FD_ZERO(&inset1);
		 FD_SET(fds[0],&inset1);
		 FD_ZERO(&inset2);
		 FD_SET(fds[1],&inset2);
		 tv.tv_sec=2;
		 tv.tv_usec=0;
		 while(FD_ISSET(fds[0],&inset1)||FD_ISSET(fds[1],&inset2))
		 {
			 if(select(maxfd+1,&inset1,&inset2,NULL,&tv)<0)
				 perror("select error!");
			 else
			 {
				if(FD_ISSET(fds[0],&inset1))
				 {
					 rc=read(fds[0],buf,7);
					 if(rc>0)
					 {
						 buf[rc]='\0';
						 printf("read:%s\n",buf);
					 }else
						 perror("read error!");
				 }
				if(FD_ISSET(fds[1],&inset2))
				 {
					 rc=write(fds[1],buf,7);
					 if(rc>0)
					 {
						 buf[rc]='\0';
						 printf("rc=%d,write:%s\n",rc,buf);
					 }else
						 perror("write error!");
					 sleep(10);
				 }
			 }
		 }
		 return 1;
	 }
}


