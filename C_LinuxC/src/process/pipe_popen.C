#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/wait.h>

namespace pipe_popen
{

	const int  BUFSIZE=1024;
	int main(int argc, char* argv[])
	{
		FILE * fp;
		char * cmd="ps -ef ";
		char buf[BUFSIZE];
		buf[BUFSIZE]='\0';
		if((fp=popen(cmd,"r"))==NULL)
			perror("popen error!");
		while((fgets(buf,BUFSIZE,fp))!=NULL)
		{
			printf("%s",buf);
		}
		pclose(fp);
	}
}
