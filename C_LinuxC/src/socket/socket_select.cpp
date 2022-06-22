
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>


namespace  select_fdset_ioctl{



int main(int argc, char *argv[])
{
    char buffer[128];
    int result, nread;

    fd_set inputs, testfds;//文件描述符 集合
    struct timeval timeout;

    FD_ZERO(&inputs);
    FD_SET(0,&inputs);//还有 FD_CLR清除 , FD_ISSET 是否在集合中

/*  Wait for input on stdin for a maximum of 2.5 seconds.  */

    while(1) {
        testfds = inputs;
        timeout.tv_sec = 2;
        timeout.tv_usec = 500000;

        //FD_SETSIZE  是为 fd_set里最大数量
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, &timeout);
        /* 第一个参数是测试从0到n-1个文件描述符,
         * 第二参数测试是否可读的文件描述符集合,
         * 第三个参数测试是否可写的文件描述符集合
         * 第四个参数测试是否有错误的文件描述符集合
         * 第五个参数超时时间,如参数为空会一直阻塞,如超时所有集合都会被清空,linux还会修改timeout为剩余超时时间
         * 如果那三个集合中,如有一个测试可以操作,函数返回,并修改对就应的文件述符集合为正在操作的(和返回的一样),如三个集合中有一个为NULL对应的就不会被测试
         *如超时返回0,－1错误,>0 是三个集合中的件描述符(和修改集合的一样)
         */

/*  After this time, we test result. If there has been no input, the program loops again.
    If there has been an error, the program exits.  */

        switch(result) {
        case 0:
            printf("timeout\n");
            break;
        case -1:
            perror("select");
            exit(1);

/*  If, during the wait, we have some action on the file descriptor,
    we read the input on stdin and echo it whenever an <end of line> character is received,
    until that input is Ctrl-D.  */

        default:
            if(FD_ISSET(0,&testfds)) {
                ioctl(0,FIONREAD,&nread);//向0文件描述符发送命令和参数,FIONREAD就是返回缓冲区内有多少字节FIONREA=File IO N read
                if(nread == 0) {//按ctrl＋D的情况
                    printf("keyboard done\n");
                    exit(0);
                }
                nread = read(0,buffer,nread);
                buffer[nread] = 0;
                printf("read %d from keyboard: %s", nread, buffer);
            }
            break;
        }
    }
}


}
