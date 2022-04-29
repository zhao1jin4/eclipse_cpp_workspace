#include "main.h"

#include <stdlib.h>
#include <stdio.h>


//	const int *A 或  int const *A; //const修饰指向的对象，A可变，A指向的对象不可变
//	int *const A;            //const修饰指针A，     A不可变，A指向的对象可变
//	const int *const A;      //指针A和A指向的对象都不可变
int main (int  argc, char* argv[])
{
	setbuf(stdout, NULL);//CDT 工具必须调用这个才立即输出到控制台,全局的
	//fflush(stdout);//CDT 工具必须调用这个才立即输出到控制台，局部的

	  openssl::main(argc, argv);//这个lib正常

	  //sqlite3 ,win64可能lib的问题目前影响启动
//	  sqlite::main(argc, argv);

	  //mysql ,win64可能lib的问题目前影响启动
//	  mysql_c::main(argc, argv);
//	  mysql_c_crud::main(argc, argv);//不支持中文？

//	  mysql8_cpp::main(argc, argv);//空
//	  mongoDB::main(argc, argv);//not work???



	return 1;

}
