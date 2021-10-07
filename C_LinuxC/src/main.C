#include "main.h"
/*
Debug默认是不能显示源码的,报错,/cygdrive/d/Program/
要设置 Window -> Preferences -> C/C++ -> Debug->Source Lookup Path -> Add->Path Mapping->Add->
输入 \cygdrive\d	对应 d:\,就OK了
*/
int main(int argc, char *argv[])
{


	//---------------
	int param_argc=2;
	char *param_argv[2];
	param_argv[0]="tcp_server";
	param_argv[1]="8181";
	return socket_tcp_server::main(param_argc,param_argv);
	//---------------
//	int param_argc=4;
//	char *param_argv[4];
//	param_argv[0]="tcp_client";
//	param_argv[1]="127.0.0.1";
//	param_argv[2]="hello world!";
//	param_argv[3]="8181";
//	return socket_tcp_client::main(param_argc,param_argv);
	//-- g++ -c *.C socket/*.C
	//-- g++ -o tcp_client *.o
	//---------------
//	int param_argc=2;
//	char *param_argv[2];
//	param_argv[0]="udp_server";
//	param_argv[1]="8282";
//	return socket_udp_server::main(argc,argv);
	//---------------
//	int param_argc=4;
//	char *param_argv[4];
//	param_argv[0]="tcp_client";
//	param_argv[1]="127.0.0.1";
//	param_argv[2]="hello world!";
//	param_argv[3]="8181";
//	return socket_udp_client::main(argc,argv);
	//---------------
//	int param_argc=2;
//	char *param_argv[2];
//	param_argv[0]="dns";
//	param_argv[1]="www.baidu.com";
//	return dns::main(param_argc,param_argv);
	//---------------

	//return fork_process::main(argc,argv);
	//return exec_process::main(argc,argv);
	//return pipe_process::main(argc,argv);
	//return pipe_popen::main(argc,argv);

	//return signal_process::main(argc,argv);
	//return signal_timer::main(argc,argv);
	//return signal_set::main(argc,argv);
	//return daemon_process::main(argc,argv);
	//---------
//	int param_argc=2;
//	char *param_argv[2];
//	param_argv[0]="file_lock";
//	param_argv[1]="c:/temp/lock.txt";
//	return file_lock::main(param_argc,param_argv);
	//---------
	//return file_select::main(argc,argv);
	//...
	//---------
//	return regex::main(argc,argv);//regexp过时了,用regex
//	return dir::main(argc,argv);
//	return memory::main(argc,argv);

}



