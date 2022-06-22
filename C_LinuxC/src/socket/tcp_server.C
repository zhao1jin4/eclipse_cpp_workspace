
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>


namespace socket_tcp_server
{

//TCP要关闭连接
//回显服务器(TCP)

#define MAXPENDING 5    /* Max connection requests */
#define BUFFSIZE 32
void Die(char *mess)
{
	perror(mess);
	exit(1);
}

void HandleClient(int sock)
{
	char buffer[BUFFSIZE];
	int received = -1;
	if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
	{
		Die("Failed to receive initial bytes from client");///有警告,不建议使用从字符串常量到‘char*’的转换
	}
	/* Send bytes and check for more incoming data in loop */
	while (received > 0)
	{
		//在写socket时,读的那一个端(客户端连接断了)关闭,会生产SIGPIPE信号
		/* Send back received data */
		if (send(sock, buffer, received, 0) != received)
		{
			Die("Failed to send bytes to client");
		}
		/* Check for more data */
		if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
		{
			Die("Failed to receive additional bytes from client");
		}
	}
	close(sock);
}

int main(int argc, char *argv[])
{
	printf("short== short int:%d",sizeof(short int) ==	sizeof(short));

	int serversock, clientsock;
	struct sockaddr_in echoserver, echoclient;//in=Internet  要<netinet/in.h>
	//sockaddr_in6 是为IPV6

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: echoserver <port>\n");
		exit(1);
	}
	//PF=protocol family
	if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)//PF_INET6是IPV6版本的
	{
		Die("Failed to create socket");
	}
	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
	echoserver.sin_family = AF_INET; /* Internet/IP */

	echoserver.sin_addr.s_addr = htonl(INADDR_ANY); //s_=sock,htonl=host to net long,INADDR_ANY 是0.0.0.0
	//echoserver.sin_addr.s_addr =inet_addr("127.0.0.1");//<arpa/inet.h>
	//arp=Address Resolution Protocol, 有arpaname 192.168.0.1命令
	echoserver.sin_port = htons(atoi(argv[1])); //htons=host to net short

	//IPPORT_RESERVED //端口被保留最大值1024
	//IPPORT_USERRESERVED //5000

	//little endian 小端字节序：低字节存于内存低地址；高字节存于内存高地址  (intel全部是这个)
	//big endian 大端字节序：高字节存于内存低地址；低字节存于内存高地址 (网络字节序)

	/* Bind the server socket */
	if (bind(serversock, (struct sockaddr *) &echoserver, sizeof(echoserver))
			//看sockaddr_in源码最后一个属性是char[]类型,长度是根据sockaddr做减法,是可以强转的
			< 0)
	{
		Die("Failed to bind the server socket");
	}
	/* Listen on the server socket */
	if (listen(serversock, MAXPENDING) < 0)//第二个参数maximum length to which the queue of pending connections
	{
		Die("Failed to listen on server socket");
	}

	/* Run until cancelled */
	while (1)
	{
		unsigned int clientlen = sizeof(echoclient);
		fprintf(stdout, "Wait for client connection... \n");
		fflush(stdout);
		if ((clientsock = accept(serversock, (struct sockaddr *) &echoclient,
				(socklen_t*)&clientlen)) < 0)
		{
			Die("Failed to accept client connection");
		}
		fprintf(stdout, "Client connected: %s\n",
				inet_ntoa(echoclient.sin_addr));
		HandleClient(clientsock);
	}
}

}
