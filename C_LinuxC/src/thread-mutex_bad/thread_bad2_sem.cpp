
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

namespace thread_bad_sem {


void *producter_f (void *arg);
void *consumer_f (void *arg);


int buffer_has_item=0;

sem_t sem;//线程的<semaphore.h>   和进程的不一样

int running =1 ;

int main(int argc, char *argv[])
{
	pthread_t consumer_t;
	pthread_t producter_t;
	
	sem_init (&sem, 0, 16);//init,最后一次参数是初始值
	
	pthread_create(&producter_t, NULL, producter_f, NULL );
	pthread_create(&consumer_t, NULL,  consumer_f, NULL);
	sleep(1);
	running =0;
	pthread_join(consumer_t,NULL);
	pthread_join(producter_t,NULL);
	sem_destroy(&sem);//destroy
	
	return 0;
}

void *producter_f (void *arg)
{
	int semval=0;
	while(running)
	{
		//usleep(1);//microseconds <unistd.h>
		sem_post (&sem);//加1
		sem_getvalue(&sem,&semval);//可以得到值
		printf("生产，总数量:%d\n",semval);
	}
}

void *consumer_f(void *arg)
{
	int semval=0;
	while(running)
	{
		//usleep(1);
		sem_wait(&sem);//减到0阻塞
		sem_getvalue(&sem,&semval);
		printf("消费，总数量:%d\n",semval);
	}
}
}
