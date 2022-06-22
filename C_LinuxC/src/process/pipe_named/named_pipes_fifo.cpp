#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
namespace pipe_named
{

	int create( )
	{

		//命名管道FIFO(好处是可用于不相关的两个进程),　有命令行 mkfifo /tmp/myfifo 或 mknod /tmp/myfifo2 p , 用ls -lF命令权限最前显示为 p,最后标识显示|
		//可用unlink或rm命令删除,unlink  /tmp/myfifo2
		int res = mkfifo("/tmp/my_fifo", 0777);//会和umask计算得出权限

		 //方式二
		 //mknod ("/tmp/my_fifo", 0777|S_IFIFO, 0);

		if (res == 0)
			printf("FIFO created\n");
		exit(EXIT_SUCCESS);
		/*
		 cat < /tmp/my_fifo 会阻塞,除非&
		另一终端
		echo "xx">  /tmp/my_fifo
		*/
	}

//可以使用open函数打开,但不能同时读和写,只能读或者写

#define FIFO_NAME "/tmp/my_fifo"

int open_none_blocking(int argc, char* argv[])
{

    int res;
    int open_mode = 0;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <some combination of\
               O_RDONLY O_WRONLY O_NONBLOCK>\n", *argv);
        exit(EXIT_FAILURE);
    }

// Assuming that the program passed the test, we now set the value of open_mode
// from those arguments.

    for(i = 1; i < argc; i++) {
        if (strncmp(*++argv, "O_RDONLY", 8) == 0)
             open_mode |= O_RDONLY;
        if (strncmp(*argv, "O_WRONLY", 8) == 0)
             open_mode |= O_WRONLY;
        if (strncmp(*argv, "O_NONBLOCK", 10) == 0)
             open_mode |= O_NONBLOCK;
     }

// We now check whether the FIFO exists and create it if necessary.
// Then the FIFO is opened and output given to that effect while the program
// catches forty winks. Last of all, the FIFO is closed.

    if (access(FIFO_NAME, F_OK) == -1) {//F_OK表示存在吗?
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO\n", getpid());
    res = open(FIFO_NAME, open_mode);
    printf("Process %d result %d\n", getpid(), res);
    sleep(5);
    if (res != -1) {
    	(void)close(res);
    }else{
    	char * reason=strerror(errno);//errno.h,string.h
    	fprintf(stderr,"error! %s\n",reason);
    }
    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);

}

int main(int argc, char* argv[])
{
	 //create();
	//----
	int param_argc=2;
	char* param_argv[]={"my","O_RDONLY"};//不加O_NONBLOCK会阻塞open函数
//	char* param_argv[]={"my","O_WRONLY"};//如果以写阻塞(O_WRONLY)方式打开,会使用PIPE_BUF缓存,如数据未满要么不写,要么写
	//写阻塞(O_WRONLY)每次写<=PIPE_BUF大小的数据,即使多个进程同时向一个管道写,系统也能保证不会交错在一起.
	//PIPE_BUF 在 <limits.h>
//	open_none_blocking(param_argc,param_argv);

	param_argc=3;
	//char* param_argv[]={"my","O_RDONLY","O_NONBLOCK"};
	//open_none_blocking(param_argc,param_argv);


	/*
	//如果没有以读打开命名管道,以非阻塞写(O_WRONLY|O_NONBLOCK)的方试的打开会失败
	param_argc=3;
	char* param_argv[]={"my","O_WRONLY","O_NONBLOCK"};
	open_none_blocking(param_argc,param_argv);
	*/
	//----

	 //time <cmd> 显示命令的运行时间
}

}
