
	#include<sys/types.h>
	#include<unistd.h>
	#include<errno.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include <sys/wait.h>
namespace pipe_process_adv
{


	int main(int argc, char* argv[])
	{

	    int data_processed;
	    int file_pipes[2];
	    const char some_data[] = "123";
	    pid_t fork_result;

	    if (pipe(file_pipes) == 0) {
	        fork_result = fork();
	        if (fork_result == (pid_t)-1) {
	            fprintf(stderr, "Fork failure");
	            exit(EXIT_FAILURE);
	        }

	        if (fork_result == (pid_t)0) {
	            close(0);//关闭0文件描述符,即stdin 最小的
	            dup(file_pipes[0]);//返回新的文件描述符,是可用的最小的,因0已关闭,这里返回0,即自己文件描述符批指向0
	            close(file_pipes[0]);//自己文件描述符0还是存在的
	            close(file_pipes[1]);

	            execlp("od", "od", "-c", (char *)0);
	            exit(EXIT_FAILURE);
	        }
	        else {
	            close(file_pipes[0]);//开进程前创建的文件描述符,每个进程都要单独关闭
	            data_processed = write(file_pipes[1], some_data,
	                                   strlen(some_data));
	            close(file_pipes[1]);
	            printf("%d - wrote %d bytes\n", (int)getpid(), data_processed);
	        }
	    }
	    exit(EXIT_SUCCESS);

	}
}
