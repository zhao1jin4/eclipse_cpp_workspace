#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


//gcc -fPIC -shared calc.c -o libcalc.so
//g++ -o test_calc test_calc.c  -l dl
//---这个可以成功
int main_dl01()
{
  void *handle;
  char *error;
  typedef int (*FUNC)(int, int);
  FUNC func = NULL;
  //打开动态链接库
  handle = dlopen("./libcalc.so", RTLD_LAZY);
  //http://www.codebaoku.com/it-c/it-c-242369.html
  //获取一个函数
  //*(void **) (&func) = dlsym(handle, "add");//dlsym返回void*,可以成功
  *((void **) (&func)) = dlsym(handle, "add");//就是func3取地址，再强制为void ** 类型，再取值，再赋值(即先强转再赋值)

  char *perr = NULL;
  perr = dlerror();
  if(perr != NULL)
  {
	printf("dlsym add error:%s\n",perr);//一样的
	return 0;
  }

  printf("add: %d\n", (*func)(2,7));
  printf("add: %d\n", func(2,7));

  //关闭动态链接库
  dlclose(handle);
}
