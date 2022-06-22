#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>

//#include <sys/ipc.h> //新的,没用的sys/sem.h里面会导入这个
#include <sys/sem.h> //新的

//#include <linux/sem.h>这个不能引入,报重复定义
#include "semun.h"//man semctl里有的,<linux/sem.h>里也有

namespace ipc_sempaphore_pv{

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);

static int sem_id;

//p(plus,pass进入临界区) 减1操作, 如为0挂起
//v 如有挂起就恢复运行,没有就加1操作
/*
inter-process communication (IPC)
ipcs 命令可查Message Queues,Shared Memory,Semaphore的使用情况

ipcrm -s 0
   -S, --semaphore-key
   -s, --semaphore-id
*/

int main(int argc, char *argv[])
{
    int i;
    int pause_time;
    char op_char = 'O';

    srand((unsigned int)getpid());//随机种子

    //第一个参数,唯一key,第二参数是数量.第三个权限,如加IPC_CREAT有已经建立过也不会报错,如要报错再|IPC_EXCL (exclusive)
    //key可传IPC_PRIVATE 只有当前进程可以仿问,说是不经常用的
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);//后面都使用返回值(>0)操作

//    key_t ftok(const char *path, int id);//ftok=file to key
//    	path必须是已经存在的(书上说必须是目录),id致少8位,要>0,
//    	返回IPC key ,为semget,msgget,shmget函数的第一个参数使用

    if (argc > 1) {
        if (!set_semvalue()) {
            fprintf(stderr, "Failed to initialize semaphore\n");
            exit(EXIT_FAILURE);
        }
        op_char = 'X';
        sleep(2);
    }

/* Then we have a loop which enters and leaves the critical section ten times.
 There, we first make a call to semaphore_p which sets the semaphore to wait, as
 this program is about to enter the critical section. */

    for(i = 0; i < 10; i++) {

        if (!semaphore_p()) exit(EXIT_FAILURE);
        printf("%c", op_char);fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        printf("%c", op_char);fflush(stdout);

/* After the critical section, we call semaphore_v, setting the semaphore available,
 before going through the for loop again after a random wait. After the loop, the call
 to del_semvalue is made to clean up the code. */

        if (!semaphore_v()) exit(EXIT_FAILURE);

        pause_time = rand() % 2;
        sleep(pause_time);
    }

    printf("\n%d - finished\n", getpid());

    if (argc > 1) {
        sleep(10);
        del_semvalue();
    }

    exit(EXIT_SUCCESS);
}

/* The function set_semvalue initializes the semaphore using the SETVAL command in a
 semctl call. We need to do this before we can use the semaphore. */

static int set_semvalue(void)
{
    union semun sem_union;//senum 是自己定义的名字,X/Open要求程序员自己来做,man semctl里有的,直接复制(<linux/sem.h>里也有,不能include报重复定义)

    sem_union.val = 1;
    //第二个参数是编号,0是第一个.第三参数 SETVAL 设置值,要求有val成员
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
    	return(0);
    return(1);
}

/* The del_semvalue function has almost the same form, except the call to semctl uses
 the command IPC_RMID to remove the semaphore's ID. */

static void del_semvalue(void)
{
    union semun sem_union;

    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)//IPC_RMID 删除不再用的
        fprintf(stderr, "Failed to delete semaphore\n");
}

/* semaphore_p changes the semaphore by -1 (waiting). */

static int semaphore_p(void)
{
    struct sembuf sem_b;//<sys/sem.h>

    sem_b.sem_num = 0;//编号,0表示第一个
    sem_b.sem_op = -1;  //-1就是P操作,1就是V操作
    sem_b.sem_flg = SEM_UNDO;//SEM_UNDO表示如果进程没有释放信号量,就让操作系统自动释放
    if (semop(sem_id, &sem_b, 1) == -1) {//第三个参数是数组的个数
        fprintf(stderr, "semaphore_p failed\n");
        return(0);
    }
    return(1);
}

/* semaphore_v is similar except for setting the sem_op part of the sembuf structure to 1,
 so that the semaphore becomes available. */

static int semaphore_v(void)
{
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = 1; /* V() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_v failed\n");
        return(0);
    }
    return(1);
}

}
