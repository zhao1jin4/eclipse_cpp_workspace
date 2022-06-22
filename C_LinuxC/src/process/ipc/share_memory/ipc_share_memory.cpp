/* Our first program is a consumer. After the headers the shared memory segment
 (the size of our shared memory structure) is created with a call to shmget,
 with the IPC_CREAT bit specified. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace ipc_share_memory{


#define TEXT_SZ 2048

struct shared_use_st {
    int written_by_you;
    char some_text[TEXT_SZ];
};

void receiver()
{
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    int shmid;

    srand((unsigned int)getpid());

    //权限可用于创建用户可写,其它用户只读
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);//<sys/shm.h>

    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

/* We now make the shared memory accessible to the program. */
    //at=attach 连接到进程的地址空间,第二个参数NULL表示让系统生成空间,第三个参数可选值有 SHM_RND,SHM_RDONLY只读
    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n",  shared_memory);

/* The next portion of the program assigns the shared_memory segment to shared_stuff,
 which then prints out any text in written_by_you. The loop continues until end is found
 in written_by_you. The call to sleep forces the consumer to sit in its critical section,
 which makes the producer wait. */

    shared_stuff = (struct shared_use_st *)shared_memory;
    shared_stuff->written_by_you = 0;
    while(running) {
        if (shared_stuff->written_by_you) {
            printf("You wrote: %s", shared_stuff->some_text);
            sleep( rand() % 4 ); /* make the other process wait for us ! */
            shared_stuff->written_by_you = 0;
            if (strncmp(shared_stuff->some_text, "end", 3) == 0) {
                running = 0;
            }
        }
    }

/* Lastly, the shared memory is detached and then deleted. */

    //dt=detach,分离并没有删除
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    //IPC_RMID删除一个正在连接的内存,是不确定的,还有IPC_SET设置权限,IPC_STAT查权限,第三个参数为shmid_ds类型
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
void sender()
{
	int running = 1;
	    void *shared_memory = (void *)0;
	    struct shared_use_st *shared_stuff;
	    char buffer[BUFSIZ];
	    int shmid;

	    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

	    if (shmid == -1) {
	        fprintf(stderr, "shmget failed\n");
	        exit(EXIT_FAILURE);
	    }

	    shared_memory = shmat(shmid, (void *)0, 0);
	    if (shared_memory == (void *)-1) {
	        fprintf(stderr, "shmat failed\n");
	        exit(EXIT_FAILURE);
	    }

	    printf("Memory attached at %X\n", shared_memory);

	    shared_stuff = (struct shared_use_st *)shared_memory;
	    while(running) {
	        while(shared_stuff->written_by_you == 1) {
	            sleep(1);
	            printf("waiting for client...\n");
	        }
	        printf("Enter some text: ");
	        fgets(buffer, BUFSIZ, stdin);

	        strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
	        shared_stuff->written_by_you = 1;

	        if (strncmp(buffer, "end", 3) == 0) {
	                running = 0;
	        }
	    }

	    if (shmdt(shared_memory) == -1) {
	        fprintf(stderr, "shmdt failed\n");
	        exit(EXIT_FAILURE);
	    }
	    exit(EXIT_SUCCESS);
}

/*
ipcrm -m 0
-M, --shmem-key
-m, --shmem-id

*/
int main(int argc, char *argv[])
{
	//和semaphore 函数形式一样的
	//共享内存没有同步机制
	if(argc>1)
	{
		  printf("----receiver...\n");
		receiver();
	}
	else
	{
		printf("----sender...\n");
		sender();
	}
}

}
