#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

namespace c11_lamda{

bool  cmp(int a, int b)
{
    return  a < b;
}
struct MyStruct{
	int x;
	int y;
};

void myLamada(){
	vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
	vector<int> lbvec(myvec);
	//<algorithm>
	sort(myvec.begin(), myvec.end(), cmp); // 旧式做法
	cout << "predicate function:" << endl;
	for (int it : myvec)
		cout << it << ' ';
	cout << endl;

	sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda表达式
	cout << "lambda expression:" << endl;
	for (int it : lbvec)
		cout << it << ' ';
	cout <<  endl;

	int a = 123;
	auto f = [a] { cout << a << endl; };//最前面的方括号[]来明确指明其内部可以访问的外部变量
	f(); // 输出：123

	//或通过“函数体”后面的‘()’传入参数
	[](int a){cout << a << endl;}(123);

	{
		int a = 123;
		auto f = [a] { cout << a << endl; };//类似闭包，会保存变量值，无参数可省略()
		a = 321;
		f(); // 输出：123

		a = 123;
		auto f1 = [&a] { cout << a << endl; };//引用传递，同函数参数
		a = 321;
		f1(); // 输出：321

		//隐式捕获有两种方式，分别是[=] 表示值 和 [&]表示引用
	    a = 123;
	    auto f3 = [=] { cout << a << endl; };    // 值捕获
	    a = 321;
	    f3(); // 输出：123

	    a = 123;
		auto f4 = [&] { cout << a << endl; };    // 引用捕获
		a = 321;
		f4(); // 输出：321

		int b=30;
		[=,&a](int i) mutable { //=,&a表示除了a变量引用,还有this，其它全是值传递
			b++; //mutable才可修改
			cout << a << endl;
		}(10);//传参数

		[]()  mutable->  float{ //->可有可无，后面是返回类型,也可省
			 return 1.3f;
		 };

		function<MyStruct(int)> f2 =[] (int i) mutable -> MyStruct{ //function<MyStruct(int)> 表示返回MyStruct参数为int，可省略为 function
			return {i,3};//参数列表时，返回类型不能省
		};

		// 绑定可调用函数
		function<int(int)> ff3 = bind([](int a) {return a; }, placeholders::_1);
		int res=ff3(20);//20传给placeholders::_1 再传给 a,再调用

		//对于没有捕获任何变量的 lambda 表达式，还可以转换成一个普通的函数指针：
		using func_ptr = int(*)(int);
		func_ptr fx = [](int a) //省略返回
		{
		    return a;
		};
		// 函数调用
		res=fx(1314);

	}
	cout <<  endl;
}

	int main(int argc, char* argv[])
	{
		 myLamada();

		 return 1;
	}
};
