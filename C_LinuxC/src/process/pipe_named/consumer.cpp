#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
namespace pipe_named_consumer
{

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF //PIPE_BUF 在 <limits.h>


	void producer()
	{


		#define TEN_MEG (1024 * 1024 * 10)

	    int pipe_fd;
	    int res;
	    int open_mode = O_WRONLY;
	    int bytes_sent = 0;
	    char buffer[BUFFER_SIZE + 1];

	    if (access(FIFO_NAME, F_OK) == -1) {
	        res = mkfifo(FIFO_NAME, 0777);
	        if (res != 0) {
	            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
	            exit(EXIT_FAILURE);
	        }
	    }

	    printf("Process %d opening FIFO O_WRONLY\n", getpid());
	    pipe_fd = open(FIFO_NAME, open_mode);
	    printf("Process %d result %d\n", getpid(), pipe_fd);

	    if (pipe_fd != -1) {
	        while(bytes_sent < TEN_MEG) {
	        	//buffer未初始化数据
	            res = write(pipe_fd, buffer, BUFFER_SIZE);
	            if (res == -1) {
	                fprintf(stderr, "Write error on pipe\n");
	                exit(EXIT_FAILURE);
	            }
	            bytes_sent += res;
	        }
	        (void)close(pipe_fd);
	    }
	    else {
	        exit(EXIT_FAILURE);
	    }

	    printf("Process %d finished\n", getpid());
	    exit(EXIT_SUCCESS);

	}

	int consumer(){

		int pipe_fd;
		int res;
		int open_mode = O_RDONLY;
		char buffer[BUFFER_SIZE + 1];
		int bytes_read = 0;

		memset(buffer, '\0', sizeof(buffer));

		printf("Process %d opening FIFO O_RDONLY\n", getpid());
		pipe_fd = open(FIFO_NAME, open_mode);
		printf("Process %d result %d\n", getpid(), pipe_fd);

		if (pipe_fd != -1) {
			do {
				res = read(pipe_fd, buffer, BUFFER_SIZE);
				//读到没有处理
				bytes_read += res;
			} while (res > 0);
			(void)close(pipe_fd);
		}
		else {
			exit(EXIT_FAILURE);
		}

		printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
		exit(EXIT_SUCCESS);
	}
	int main(int argc, char* argv[])
	{
		//如双向通信,要两个管道
		if(argc>1)
		{
			printf("----consumer...\n");
			consumer();
		}
		else
		{
			printf("----producer...\n");
			producer();
		}

	}
}
