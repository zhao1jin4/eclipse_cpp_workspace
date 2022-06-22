#include "main.h"
#include <stdlib.h>
#include <stdio.h>
/*
Debug默认是不能显示源码的,报错,/cygdrive/d/Program/
要设置 Window -> Preferences -> C/C++ -> Debug->Source Lookup Path -> Add->Path Mapping->Add->
输入 \cygdrive\d	对应 d:\,就OK了
*/

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);//CDT 工具必须调用这个才立即输出到控制台,全局的
	//fflush(stdout);//CDT 工具必须调用这个才立即输出到控制台，局部的

//	lib_get_etc_name::main(argc,argv);
	lib_inet_xxx::main(argc,argv);//有未测试的,还不全....

//	socket_unix_server::main(argc,argv);
//	socket_unix_client::main(argc,argv);

//	select_fdset_ioctl::main(argc,argv);

	//---------------
//	int param_argc=2;
//	char *param_argv[2];
//	param_argv[0]="tcp_server";
//	param_argv[1]="8181";
//	socket_tcp_server::main(param_argc,param_argv);
	//---------------
//	int param_argc=4;
//	char *param_argv[4];
//	param_argv[0]="tcp_client";
//	param_argv[1]="127.0.0.1";
//	param_argv[2]="hello world!";
//	param_argv[3]="8181";
//	socket_tcp_client::main(param_argc,param_argv);

	//-- g++ -c *.C socket/*.C
	//-- g++ -o tcp_client *.o
	//---------------
//	int param_argc=2;
//	char *param_argv[2];
//	param_argv[0]="udp_server";
//	param_argv[1]="8282";
//	socket_udp_server::main(param_argc,param_argv);
	//---------------
//	int param_argc=4;
//	char *param_argv[4];
//	param_argv[0]="tcp_client";
//	param_argv[1]="127.0.0.1";
//	param_argv[2]="hello world!";
//	param_argv[3]="8282";
//	socket_udp_client::main(param_argc,param_argv);
	//---------------
//	int param_argc=2;
//	char *param_argv[2];
//	param_argv[0]="dns";
//	param_argv[1]="www.baidu.com";
//	dns::main(param_argc,param_argv);

	//--------process
//	fork_process::main(argc,argv);
//	exec_process::main(argc,argv);
//	daemon_process::main(argc,argv);

	//---signal
//	signal_process::main(argc,argv);
//	signal_timer::main(argc,argv);
//	signal_set::main(argc,argv);

	//---pipe
//	pipe_popen::main(argc,argv);
//	pipe_process::main(argc,argv);
//	pipe_process_adv::main(argc,argv);
//	pipe_named::main(argc,argv);
//	pipe_named_consumer::main(argc,argv);
	//---ipc
//	ipc_sempaphore_pv::main(argc,argv);
//	ipc_share_memory::main(argc,argv);
//	ipc_msg_queue::main(argc,argv);
//	ipc_msg_queue_change::main(argc,argv);

	//---------file
	//file_lock::main(argc,argv);
	//file_select::main(argc,argv);
	//dir::main(argc,argv);
	//memory_map::main(argc,argv);
	//file_stat::main(argc,argv);
	//file_control::main(argc,argv);
	//file_ioctl::main(argc,argv);

	//---bad
	//file_bad::main(argc,argv);
//	thread_bad_basic::main(argc,argv);
//	thread_bad_sem::main(argc,argv);
//	thread_bad_mutex::main(argc,argv);
//	thread_bad_detach_sem::main(argc,argv);
//	thread_bad_attr::main(argc,argv);
//	thread_bad_cancel::main(argc,argv);

	//---lib
//	regex::main(argc,argv);//regexp过时了,用regex
//	lib_gettext::main(argc,argv);
//	lib_cmd::main(argc,argv);
//	lib_util::main(argc,argv);
//	 lib_log_limit::main(argc,argv);//程序会因限制异常退出

	return 0;
}



