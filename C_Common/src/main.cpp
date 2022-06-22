#include "main.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);//CDT 工具必须调用这个才立即输出到控制台,全局的
	//fflush(stdout);//CDT 工具必须调用这个才立即输出到控制台，局部的

	c_basic::main(argc, argv);
//	cpp_basic::main(argc, argv);
//	cpp_const::main(argc, argv);
//	cpp_equal::main(argc, argv);
//	stl_c::main(argc, argv);
//	stl_jmp::main(argc, argv);
//	stl_signal::main(argc, argv);
//	stl_arg::main(argc, argv);
//	stl_search_sort::main(argc, argv);
//	stl_chinese::main(argc, argv);
//	stl_chinese_gbk::main(argc, argv);
//	stl_cpp::main(argc, argv);
//
//	exercise::main(argc, argv);
//	sort::main(argc, argv);
//	no_recursive::main(argc, argv);
//	quiz_reverse::main(argc, argv);
//	quiz_function_statck::main(argc, argv);



	return 1;

}

