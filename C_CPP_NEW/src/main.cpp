#include "main.h"

#include <stdlib.h>
#include <stdio.h>

int main(int  argc, char* argv[])
{

	/*VC2019 中	strcpy ,fopen 函数报不安全错误
	项目->属性->C/C++->预处理器(preprocessor)->预处理器定义(preprocessor Definitions)中添加 _CRT_SECURE_NO_WARNINGS 这个预定义。
		如使用swprintf函数就要加， _CRT_NON_CONFORMING_SWPRINTFS
	*/

	setbuf(stdout, NULL);//CDT 工具必须调用这个才立即输出到控制台,全局的
	//fflush(stdout);//CDT 工具必须调用这个才立即输出到控制台，局部的
/*
	//lib
  	c11_wchar::main(argc,argv);
	c11_wctype::main(argc,argv);
	c11_time::main(argc,argv);

	//grammar
	c11_contructor::main(argc,argv);
	c11_final_override::main(argc,argv);
	c11_init::main(argc,argv);
	c11_auto::main(argc,argv);
	c11_decltype::main(argc,argv);
	c11_lamda::main(argc,argv);
	c11_using::main(argc,argv);

	c11_func_bind::main(argc,argv);//vc有不行的，类对象转换为函数指针 不能和重载()一起用

	cpp11new::main(argc,argv);

	c11_move_forward::main(argc,argv);
	c11_smart_ptr::main(argc,argv);
	c11_smart_ptr_weaklock::main(argc,argv);


	//thread ，里面应该有不安全的内存仿问
//	c11_thread_notify::main(argc,argv);
//	c11_thread_promise::main(argc,argv);
//	c11_thread::main(argc,argv); //linux下要加 -l pthread,原因为pthread不是linux的默认库

	//--demo 上面的c11_thread::main 会中止程序 ？？？
	//fail 执行不到这里？？ thread error ??
	//c11_thread_mem::main(argc,argv);
	move_contruct::main(argc,argv); //移动构造函数不能被调用 ？？？，可能是GCC版本比较低

	c14_new::main(argc,argv);
	c17_new::main(argc,argv);
	*/

//	c20_new::main(argc,argv);
//	c20_lib::main(argc,argv);
//	c20_container_erase::main(argc,argv);
//	c20_requires_concept::main(argc,argv);
//	c20_trivially::main(argc,argv);

	c20_coroutine::main(argc,argv);//cppreference上的示例

	//VC2019 要项目属性->C/C++->Language->Enable Experimental下拉选择module
	//c20_module::main(argc,argv);//GCC要加编译选项 -fmodules-ts


//	c20_wrong::main(argc,argv);



	return 1;
}
