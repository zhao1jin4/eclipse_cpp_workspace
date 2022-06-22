#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

namespace thread_bad_attr{

void *thread_function(void *arg);

char message[] = "Hello World";
int thread_finished = 0;

int main(int argc, char *argv[]){
    int res;
    pthread_t a_thread;
    void *thread_result;
    pthread_attr_t thread_attr;

    int max_priority;
    int min_priority;
    struct sched_param scheduling_value;

    res = pthread_attr_init(&thread_attr);//init
    if (res != 0) {
        perror("Attribute creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setschedpolicy(&thread_attr, SCHED_OTHER);//默认的
    if (res != 0) {
        perror("Setting schedpolicy failed");
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
    //取优先级的范围
    max_priority = sched_get_priority_max(SCHED_OTHER);
    min_priority = sched_get_priority_min(SCHED_OTHER);
    scheduling_value.sched_priority = min_priority;//sched_param结构体中的sched_priority
    res = pthread_attr_setschedparam(&thread_attr, &scheduling_value);//param设置优先级
    if (res != 0) {
        perror("Setting schedpolicy failed");
        exit(EXIT_FAILURE);
    }

    //pthread_attr_getinheritsched(&thread_attr);
    //pthread_attr_setinheritsched(&thread_attr,PTHREAD_EXPLICIT_SCHED);//默认为PTHREAD_EXPLICIT_SCHED
    //还有PTHREAD_INHERIT_SCHED表示新线程沿用他线程的属性


    (void)pthread_attr_destroy(&thread_attr);//destroy
    while(!thread_finished) {
        printf("Waiting for thread to say it's finished...\n");
        sleep(1);
    }
    printf("Other thread finished, bye!\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    printf("thread_function is running. Argument was %s\n", (char *)arg);
    sleep(4);
    printf("Second thread setting finished flag, and exiting now\n");
    thread_finished = 1;
    pthread_exit(NULL);
}

}
