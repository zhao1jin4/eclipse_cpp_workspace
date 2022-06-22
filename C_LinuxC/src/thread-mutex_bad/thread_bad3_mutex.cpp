#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

namespace thread_bad_mutex{
/*

void *producter_f (void *arg);
void *consumer_f (void *arg);


int buffer_has_item=0;
pthread_mutex_t mutex;

int running =1 ;

int main(int argc, char *argv[])
{
	pthread_t consumer_t;
	pthread_t producter_t;
	
	pthread_mutex_init (&mutex,NULL);
	
	pthread_create(&producter_t, NULL,producter_f, NULL );
	pthread_create(&consumer_t, NULL, consumer_f, NULL);
	usleep(1);
	running =0;
	pthread_join(consumer_t,NULL);
	pthread_join(producter_t,NULL);
	pthread_mutex_destroy(&mutex);
	
	return 0;
}

void *producter_f (void *arg)
{
	while(running)
	{
		pthread_mutex_lock (&mutex);
		buffer_has_item++;
		printf("生产，总数量:%d\n",buffer_has_item);
		pthread_mutex_unlock(&mutex);
	}
}

void *consumer_f(void *arg)
{
	while(running)
	{
		pthread_mutex_lock(&mutex);
		buffer_has_item--;	
		printf("消费，总数量:%d\n",buffer_has_item);
		pthread_mutex_unlock(&mutex);
	}

*/

//pthread_mutex_xx  函数不设置errno


void *thread_function(void *arg);
pthread_mutex_t work_mutex; /* protects both work_area and time_to_exit */

#define WORK_SIZE 1024
char work_area[WORK_SIZE];//两线程共用的内存
int time_to_exit = 0;
int main(int argc, char *argv[])
{
	  int res;
	    pthread_t a_thread;
	    void *thread_result;
	    res = pthread_mutex_init(&work_mutex, NULL);//init
	    if (res != 0) {
	        perror("Mutex initialization failed");
	        exit(EXIT_FAILURE);
	    }
	    res = pthread_create(&a_thread, NULL, thread_function, NULL);
	    if (res != 0) {
	        perror("Thread creation failed");
	        exit(EXIT_FAILURE);
	    }
	    pthread_mutex_lock(&work_mutex);//加锁,线程建立后
	    printf("Input some text. Enter 'end' to finish\n");
	    while(!time_to_exit) {
	        fgets(work_area, WORK_SIZE, stdin);
	        pthread_mutex_unlock(&work_mutex);//解锁
	        while(1) {
	            pthread_mutex_lock(&work_mutex);
	            if (work_area[0] != '\0') {
	                pthread_mutex_unlock(&work_mutex);
	                sleep(1);
	            }
	            else {
	                break;
	            }
	        }
	    }
	    pthread_mutex_unlock(&work_mutex);
	    printf("\nWaiting for thread to finish...\n");
	    res = pthread_join(a_thread, &thread_result);
	    if (res != 0) {
	        perror("Thread join failed");
	        exit(EXIT_FAILURE);
	    }
	    printf("Thread joined\n");
	    pthread_mutex_destroy(&work_mutex);//destroy
	    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    sleep(1);
    pthread_mutex_lock(&work_mutex);
    while(strncmp("end", work_area, 3) != 0) {
        printf("You input %d characters\n", strlen(work_area) -1);
        work_area[0] = '\0';
        pthread_mutex_unlock(&work_mutex);
        sleep(1);
        pthread_mutex_lock(&work_mutex);
        while (work_area[0] == '\0' ) {
            pthread_mutex_unlock(&work_mutex);
            sleep(1);
            pthread_mutex_lock(&work_mutex);
        }
    }
    time_to_exit = 1;
    work_area[0] = '\0';
    pthread_mutex_unlock(&work_mutex);
    pthread_exit(0);
}

}
