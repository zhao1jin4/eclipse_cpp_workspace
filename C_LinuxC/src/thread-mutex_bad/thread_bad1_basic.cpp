#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

namespace thread_bad_basic {

void *thread_function(void *arg);

//全局变量,每个线程都可使用
char message[] = "Hello World";

//编译加 -l pthread
int main(int argc, char *argv[]) {
	//线程最好不要使用 errno,虽然他是一个函数


    int res;
    pthread_t a_thread;
    void *thread_result;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);//线程属性NULL,函数参数
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);//join才能得到线程返回值
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined, it returned %s\n", (char *)thread_result);
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {//函数形式,可得到参数
    printf("thread_function is running. Argument was %s\n", (char *)arg);
    sleep(3);
    strcpy(message, "Bye!");//还有strncmp
    pthread_exit((void*)"Thank you for the CPU time");//线程返回值
}

}
