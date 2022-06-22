#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//int mymax(int a,int b );
// ar crs libmy.a mylib.o
//gcc -o test test.cpp  -static -l my -L .

/**
gcc/g++
替代LD_LIBRARY_PATH的另一个方式
/lib64/ld-linux-x86-64.so.2 --library-path ./ ./test #格式为　--library-path 查找路径　程序名,不用加-l参数

 -static 当同时发动态库和静态库时　,默认使用动态库,这个强制使用静态库
	测试下来是所有的要都使用静态库,-lstdc++,-lm,-c 找不到,只能安装　libstdc++-static.x86_64 只能解决-lstdc++,再安装glibc-static 解决-lm,-lc
 */


int main_test(){
	//g++ -o libmy.so -fPIC -shared  mylib.cpp
	//g++ -o test test.cpp mylib.cpp -DOS_LINUX　可以传到源码中的　#ifdef 　来使用


	//export LD_LIBRARY_PATH=/usr/lib:$LD_LIBRARY_PATH　&& ./test 或者
	// /lib64/ld-linux-x86-64.so.2 --library-path /usr/lib:. ./test

	char* os="";
#ifdef OS_LINUX
	os="linux";
#else
	os="notlinux";
#endif
	printf("os =%s\n",os);
	//printf("mymax=%d\n",mymax(12,22));


	//---------- 以下 为何不成功???

	//gcc -o libmy.so -fPIC -shared  mylib.cpp
	//g++ -o test test.cpp   -ldl

	  char src[]="Hello Dynamic";
	  int (*pStrLenFun)(char *str);

	  void *phandle = NULL;
	  char *perr = NULL;
	  phandle = dlopen("./libmy.so", RTLD_LAZY);//RTLD_NOW ,RTLD_LAZY ,RTLD＝???
	  if(!phandle)
	  {
		printf("Failed Load library!\n");
	  }
	  perr = dlerror();
	  if(perr != NULL)
	  {
		printf("dlopen error:%s\n",perr);
		return 0;
	  }


	  typedef int (*FUNC)(int, int);
	  FUNC func1 = NULL;
	  *(void **) (&func1) = dlsym(phandle, "add");//和前面一样的代码,不行????? ldconfig -p | grep my 也没有
	  perr = dlerror();
	  if(perr != NULL)
	  {
		printf("dlsym add error:%s\n",perr);//失败???
		return 0;
	  }
	  printf("mymax: %d\n", (*func1)(2,7));



	  void* func = dlsym(phandle, "strLen");
	  perr = dlerror();
	  if(perr != NULL)
	  {
		printf("dlsym error:%s\n",perr);
		// 为何报, dlsym error:./libmy.so: undefined symbol: strLen 函数太复杂??
		return 0;
	  }
	  printf("The string is: %s\n",src);
	  pStrLenFun=( int (*)(char *))func;//函数指做强制类型转换
	  printf("the string length is: %d\n",pStrLenFun(src));
	  dlclose(phandle);

	return 1;

}
