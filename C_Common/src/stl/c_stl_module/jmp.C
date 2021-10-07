#include <setjmp.h>
#include <stdio.h>

namespace stl_jmp
{

	class MyTest
	{
	public:
		MyTest()
		{
			printf("构造一个MyTest类型的对象/n");
		}
		virtual ~ MyTest()
		{
			printf("析构销毁一个MyTest类型的对象/n");
		}
	};
	jmp_buf mark;
	void test1()
	{
		MyTest myobj;//放在这是不行的
		longjmp(mark, 1);
	}

	void test()
	{
		MyTest myobj;//放在这里是可以的
		test1();
	}

	void jmpTwo()
	{
		int jmpret;
		jmpret = setjmp( mark );
		if (jmpret == 0)
		{
			test();
		}
		else
		{
			printf("捕获到一个异常/n");
		}
	}
//---------------------------------------------------------------
	/* */
	 //测试一
	 void jmpOne()
	 {
	 //------ setjmp.h 是C中的异常处理机制,不能很好地支持C++中面向对象的语义(VC++),使用try{}catch代替,有时对象不能被析构
	 jmp_buf env;
	 int val = 0;
	 val = setjmp(env); //如果被修改可以表示有异常
	 printf("val is %d\n", val); //会执行两次
	 if (!val)
	 longjmp(env, 1); //会跳到 setjmp 处,把1做为返回值 给val ,longjmp 到 setjmp中不能有局部变量
	 }


	int main(int argc, char* argv[])
	{
		//jmpOne();
		jmpTwo();//调试报错
		return 1;
	}

}
