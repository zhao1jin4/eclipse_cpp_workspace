#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

namespace c11_func_bind{

using funcptr=int(*)(int,int);
class MyClass{
public :
	int num;
	//类对象转换为函数指针
	operator funcptr(){
		return avg; //必须是static函数
	}
	/*
	//linux下不可用 operator ()
	operator ()(int a){
		return a+1;
	}
	operator ()(int a,string b){
		cout<<b<<endl;
		return a ;
	}
	 */
	/*
	operator ()(int a,int b){ //优先级高于 operator funcptr
			cout<<b<<endl;
			return a ;
		}
	*/

	int max(int a,int b){
		return a>b?a:b;
	}
	static int avg(int a,int b){
		return (a+b)/2;
	}
};

	int myadd(int a,int b){
		return a+b;
	}

	class CaseClass{
		public:
			CaseClass(const function<int(int,int)>  &func ) : callback(func)//初始化参数
			{
			}
			int notify(int a,int b){
				return callback(a,b);
			}
		private :
			function<int(int,int)> callback;
	};

	int main(int argc, char* argv[])
	{

		funcptr ptr0=MyClass::avg;//static的
		funcptr ptr1=&MyClass::avg;//&有没有都可
		MyClass my;
		int res=my(11,22);//类对象转换为函数指针 和 运算符重载，调用哪个？测试下来调用运算符重载
		cout<<res<<endl;

//		res=my(11);//运算符重载 //linux下不行
//		res=my(22,"abc");

		using intPtr= int MyClass::*;//指向类的属性的指针
		intPtr p1=&MyClass::num;
		my.*p1=22;//属性名，可以是动态的

		using classFuncPtr= int (MyClass::*)( int,int);//指向类的函数的指针
		classFuncPtr maxPtr = &MyClass::max;
		res=(my.*maxPtr)(11,33);

		funcptr ptr3=my;//类对象转换为函数指针

		//函数包装，#include <functional>
		function<int(int,int)> f1  = MyClass::avg;
		function<int(int,int)> f2  = ptr3;
		function<int(int,int)> f3  = my;
		function<int(int,int)> f4= myadd;

		//回调示例
		CaseClass one(myadd);
		res=one.notify(2,3);
		//bind
		res=bind(myadd,1,3)();
		res=bind(myadd,placeholders::_1,20)(10);//placeholders::_1表示第一个参数，使用实参数
		res=bind(myadd,placeholders::_1,20)(10,30);//已经绑定了，值不能再修改了，


		class Test
		{
		public:
		    void output(int x, int y)
		    {
		        cout << "x: " << x << ", y: " << y << endl;
		    }
		    int m_number = 100;
		};
		Test t;
		// 绑定类成员函数
		function<void(int, int)> ff1 =
			bind(&Test::output, &t, placeholders::_1, placeholders::_2);
		// 绑定类成员变量(公共)
		function<int&(void)> ff2 = bind(&Test::m_number, &t);

		// 调用
		ff1(520, 1314);
		ff2() = 2333;
		cout << "t.m_number: " << t.m_number << endl;




		return 1;
	}
};
