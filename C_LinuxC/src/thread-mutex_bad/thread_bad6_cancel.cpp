#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

namespace thread_bad_cancel{
void *thread_function(void *arg);

int main(int argc, char *argv[]){
    int res;
    pthread_t a_thread;
    void *thread_result;

    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    sleep(3);
    printf("Canceling thread...\n");
    res = pthread_cancel(a_thread);//主线程对子线程发起取消命令
    if (res != 0) {
        perror("Thread cancelation failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int i, res, j;
    res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);//子线程设置可以被取消
    if (res != 0) {
        perror("Thread pthread_setcancelstate failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);//子线程设置取消执行类型,
    //PTHREAD_CANCEL_DEFERRED 只在执行到某个函数(如 xxx_wait,thread_join,pthread_testcancel)时线程才会停止
    //PTHREAD_CANCEL_ASYNCHRONOUS 立即停止
    if (res != 0) {
        perror("Thread pthread_setcanceltype failed");
        exit(EXIT_FAILURE);
    }
    printf("thread_function is running\n");
    for(i = 0; i < 10; i++) {
        printf("Thread is still running (%d)...\n", i);
        sleep(1);//这里可以被取消
        //pthread_testcancel();
    }
    pthread_exit(0);
}

}
