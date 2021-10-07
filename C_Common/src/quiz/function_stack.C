namespace quiz_function_statck{

#include <stdio.h>
//gcc __stdcall  __cdecl 结果都一样
//__cdecl void parameterFunc()
void parameterFunc()
{
	struct person
		{
		char name[10];
		}group[3]={{"abc"},{"def"},{"ghi"}};
		struct person * p_list=group;
		printf("%c%c%c\n",	(*(p_list+1)).name[0],//g
						(*(p_list++)).name[1],//b ,这里的++只影响前面的,不影响后面的
						(*(p_list+1)).name[2]);//f
		//结果是gbf  , C 语言的函数调用是从右向左压入栈
		//最后一个参数计算值 放入函数栈,第二个参数指针的改变不会影响最后一个参数的值

}
int main(int  argc, char* argv[])
{

	parameterFunc();

}


}
