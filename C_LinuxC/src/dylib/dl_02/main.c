#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//dl=dynamic loading　或　dynamic linking
//F=following?　for?
//CN=constants　?　construction　?

//gcc -shared -fPIC -o libhello.so hello.c
//gcc -o main main.c  -l dl          编译加　-ldl
//---这个函数简单就可以成功
//./main  1 hello
//./main  0 global

int main_dl02(int argc, char **argv)
{
    // libhello.so是我们自己封装的一个测试的共享库文件
    // RTLD_LAZY 表示在对符号引用时才解析符号，但只对函数符号引用有效，而对于变量符号的引用总是在加载该动态库的时候立即绑定解析
    void *handle = dlopen("./libhello.so", RTLD_LAZY);
    if(!handle) {
        printf("open failed: %s\n", dlerror());
        return 1;
    }
    void *p = dlsym(handle, argv[2]);  //argv[2]对应输入需获取地址的符号名
    if(!p) {
        printf("load failed: %s\n", dlerror());
        return 1;
    }
    // argv[1]对应输入0表示获取的是全局变量的符号
    // argv[1]对应输入1表示获取的是全局函数的符号
    if(0 == atoi(argv[1])) {
        printf("global is %d\n", *(int*)p);//强转为int*(不是int) 再取值*
    }else if(1 == atoi(argv[1])) {
        void (*fp)() = (void (*)())p;
        fp();
    }
    dlclose(handle);
    return 0;
}
