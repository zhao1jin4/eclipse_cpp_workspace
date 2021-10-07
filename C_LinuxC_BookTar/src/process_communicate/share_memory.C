#include<sys/types.h>
	#include<unistd.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <string.h>
	#include <sys/shm.h>
namespace share_memeory
{


	//ipcs 要在linux下使用
	int main(int argc, char* argv[])
	{
		const int BUFFER_SIZE=2048;
		int id;
		char* addr;
		if((id=shmget(IPC_PRIVATE,BUFFER_SIZE,0666))<0)
		{
			perror("shmget error !");
			exit(-1);
		}else
			printf("create shared-memory :%d\n",id);

		system("ipcs -m"); //
		if((addr=(char*)shmat(id,0,0))<0)
		{
			perror("shmat error!\n");
			exit(-1);
		}else
			printf ("attache share-memeory");

		if((shmdt(addr))<0)
		{
			perror("shmdt error!\n");
			exit(-1);
		}else
			printf ("deattache share-memeory");

		system("ipcs -m"); //


	}
}
