
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
//Fedora 9 上执行 OK)(TCP)
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
	/* Receive message */
	if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
	{
		Die("Failed to receive initial bytes from client");///有警告,不建议使用从字符串常量到‘char*’的转换
	}
	/* Send bytes and check for more incoming data in loop */
	while (received > 0)
	{
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
	struct sockaddr_in echoserver, echoclient;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: echoserver <port>\n");
		exit(1);
	}
	/* Create the TCP socket */
	if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		Die("Failed to create socket");
	}
	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
	echoserver.sin_family = AF_INET; /* Internet/IP */
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY); /* Incoming addr */
	echoserver.sin_port = htons(atoi(argv[1])); /* server port */

	//little endian 小端字节序：低字节存于内存低地址；高字节存于内存高地址  (intel全部是这个)
	//big endian 大端字节序：高字节存于内存低地址；低字节存于内存高地址 (网络字节序)

	/* Bind the server socket */
	if (bind(serversock, (struct sockaddr *) &echoserver, sizeof(echoserver))
			< 0)
	{
		Die("Failed to bind the server socket");
	}
	/* Listen on the server socket */
	if (listen(serversock, MAXPENDING) < 0)
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
