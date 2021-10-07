#include "main.h"
/*
Debug默认是不能显示源码的,报错,/cygdrive/d/Program/
要设置 Window -> Preferences -> C/C++ -> Debug->Source Lookup Path -> Add->Path Mapping->Add->
输入 \cygdrive\d	对应 d:\,就OK了
*/
int main(int argc, char *argv[])
{

	//---------------在cygwin环境下不行
	//return fifo_read::main(argc,argv);
	//return fifo_write::main(argc,argv);

	//return share_memeory::main(argc,argv);
	return message_queue::main(argc,argv);

}
