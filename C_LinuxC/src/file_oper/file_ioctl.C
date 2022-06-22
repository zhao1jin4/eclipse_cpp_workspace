#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <fcntl.h>
#include <linux/cdrom.h>

namespace file_ioctl
{

	//ioctl 向设备发送命令
	 int main(int argc, char *argv[])
	 {
		 /*打开CDROM设备文件*/
		  int fd = open("/dev/cdrom",O_RDONLY| O_NONBLOCK);//一定要加O_NONBLOCK ，否则报No medium found
		 	if(fd < 0){
		 		printf("打开CDROM失败\n");
		 		char * reason=strerror(errno);//errno.h,string.h
				fprintf(stderr,"error! %s\n",reason);
				return -1;
		 	}
		 	if (!ioctl(fd, CDROMEJECT,NULL)){ //CDROMEJECT 在 linux/cdrom.h
		 		printf("成功弹出CDROM\n");
		 	}else{
		 		printf("弹出CDROM失败\n");
		 	}
		 return 1;
	 }


}


