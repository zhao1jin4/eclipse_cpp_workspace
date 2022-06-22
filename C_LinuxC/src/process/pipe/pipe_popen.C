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
	void upper_fgets()
	{
		FILE * fp;
		char * cmd="uname -r";
		char buf[BUFSIZE];
		buf[BUFSIZE]='\0';
		if((fp=popen(cmd,"r"))==NULL)//popen=pipe open是 stdio.h中的上层标准库的,模式只可是r,w
			perror("popen error!");//p=pring
		while((fgets(buf,BUFSIZE,fp))!=NULL)
		{
			printf("%s",buf);
		}
		pclose(fp);//pclose
	}
	void upper_fread()
	{
		FILE *read_fp;
		char buffer[BUFSIZ + 1];
		int chars_read;

		memset(buffer, '\0', sizeof(buffer));
		read_fp = popen("ps -ax", "r");
		if (read_fp != NULL) {
			chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
			while (chars_read > 0) {
				buffer[chars_read - 1] = '\0';
				printf("Reading:-\n %s\n", buffer);
				chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
			}
			pclose(read_fp);
			exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
	}
	void upper_fwrite(){
		 FILE *write_fp;
		char buffer[BUFSIZ + 1];

		sprintf(buffer, "Once upon a time, there was...\n");
		write_fp = popen("od -c", "w");// od 八进制  -c ascii
		if (write_fp != NULL) {
			fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
			pclose(write_fp);
			exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
	}
	int main(int argc, char* argv[])
	{

		upper_fgets();
//		upper_fread();
//		upper_fwrite();
	}
}
