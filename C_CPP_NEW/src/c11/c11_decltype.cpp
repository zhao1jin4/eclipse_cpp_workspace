#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

namespace c11_decltype{
	const int& leftValueRef(int a, int b)//左值表示可以取地址的,locator value
	{
		return  a < b?a:b;
	}
	const int&& rightValueRef(int a, int b)//右值,read value,如2，“aabc",即不是变量，不能取地址
	{
		 return  2;
	}
	void myDelType()
	{
		const vector<int> vi;
		typedef decltype (vi.begin()) CIT;   //新的操作符 decltype 可以从一个表达式中“俘获”其结果的类型并“返回”
		CIT another_const_iterator;

		int var1=1;
		int var2=2;
		int var3;
		decltype(var1+var2) var4;
		decltype(var3=var1+var2) var5=var1;

		decltype (leftValueRef(1,2)) myLeft=22;//不会调用函数,类型为 const int&
		decltype (rightValueRef(1,2)) myRight=22;//类型为 const int&&

		const int mynum=2;
		decltype(mynum) mynum2=3;//const int
		class Myclass{
		public:
			int num;
		};
		const Myclass my{};
		decltype ((my.num)) mynumRef=mynum;//多加一层()为引用类型,如类有const,volatil 也要加上,类型为const int&

	}
	int main(int argc, char* argv[])
	{

		myDelType();

		 return 0;
	}
};
