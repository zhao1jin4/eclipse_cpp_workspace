#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

namespace thread_bad_detach_sem{

void *thread_function(void *arg);

char message[] = "Hello World";
int thread_finished = 0;

sem_t sem;

int main(int argc, char *argv[]){
	sem_init (&sem, 0, 0);//初始值0

    int res;
    pthread_t a_thread;
    void *thread_result;
    pthread_attr_t thread_attr;

    res = pthread_attr_init(&thread_attr);//attr_init
    if (res != 0) {
        perror("Attribute creation failed");
        exit(EXIT_FAILURE);
    }
    //设置成了detach就不能join了,默认是PTHREAD_CREATE_JOINABLE
    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        perror("Setting detached attribute failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&a_thread, &thread_attr, thread_function, (void *)message);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    (void)pthread_attr_destroy(&thread_attr);//attr_destroy

    printf("Waiting for all sub thread  finished...\n");
    sem_wait(&sem);//减到0阻塞
//    while(!thread_finished) {
//        printf("Waiting for thread to say it's finished...\n");
//        sleep(1);
//    }
    printf("Other thread finished, bye!\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    printf("thread_function is running. Argument was %s\n", (char *)arg);
    sleep(4);
    printf("Second thread setting finished flag, and exiting now\n");
    thread_finished = 1;

    //pthread_exit(NULL);
    sem_post (&sem);//加1主线程取消阻塞
}

}
