#include "main.h"

int main(int  argc, char* argv[])
{
	/*
	c11_wchar::main(argc,argv);
	c11_wctype::main(argc,argv);

	//grama
	c11_contructor::main(argc,argv);
	c11_final_override::main(argc,argv);
	c11_init::main(argc,argv);
	c11_auto::main(argc,argv);
	c11_decltype::main(argc,argv);
	c11_lamda::main(argc,argv);
	c11_using::main(argc,argv);
	*/
//	c11_func_bind::main(argc,argv);//linux下不可用 operator ()

//	c11_time::main(argc,argv);
	c11_thread::main(argc,argv); //linux下要加 -l pthread,原因为pthread不是linux的默认库
//	c11_thread_notify::main(argc,argv);
//	c11_thread_promise::main(argc,argv);
//	c11_thread_mem::main(argc,argv);


//	cpp11new::main(argc,argv);


//	c11_move_forward::main(argc,argv);
//	c11_intellij_ptr::main(argc,argv);

//	thread_fail::main(argc,argv);//不支持重载()？？？

//  move_contruct::main(argc,argv); //移动构造函数不能被调用 ？？？，可能是GCC版本比较低


//	c14_new::main(argc,argv);
 // c20_thread_barrier::main(argc,argv);
	//explicit, c11关键字 noexcept


	return 1;
}
