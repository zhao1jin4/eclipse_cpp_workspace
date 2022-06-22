
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>

namespace socket_unix_server{

int main(int argc, char *argv[])
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

/*  Remove any old socket and create an unnamed socket for the server.  */

    unlink("/tmp/server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);//UNIX协议

/*  Name the socket.  */

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "/tmp/server_socket");//本地socket文件

   // ls -lF /tmp/server_socket显示权限是   s开头 ,文件名以=结尾 /tmp/server_socket=
   //ps -lx 显示进程状态STAT为S (sleep) ,l表示multi-threaded,+表示前台进程,R(Runing),N低优先级,
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);
    while(1) {
        char ch;

        printf("server waiting\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, (socklen_t *)&client_len);
        //accept阻塞,可用fcnctl(socket,F_SETFL,O_NONEBLOCK|flags)设置非阻塞

/*  We can now read/write to client on client_sockfd.  */

        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}


}
