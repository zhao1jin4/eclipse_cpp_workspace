#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;
namespace c11_move_forward{

class Test
{
public:
    Test() : m_num(new int(100))
    {
        cout << "construct" << endl;
    }

    Test(const Test& a) : m_num(new int(*a.m_num))
    {
        cout << "copy & construct" << endl;
    }
    Test(Test&& a) : m_num(a.m_num)
    {
    	//只VC调用到？？？
    	a.m_num=nullptr;//两个指向同一地址，防止一个析构回了，另一个不能用
 	    cout << "move && construct" << endl;
    }
    ~Test()
    {
    	cout << "~construct:" << endl;
        delete m_num;
    }

    int* m_num;
};



	Test getTest(){
		Test t ;
		return t;
	}
	Test getConstTest(){
		return Test();
	}


	template<typename T>
	void printValue(T& t)
	{
	    cout << "l-value: " << t << endl;
	}

	template<typename T>
	void printValue(T&& t)
	{
	    cout << "r-value: " << t << endl;
	}
	template<typename T>
	void printValueR(const T&& t) //如传&a,变成 int* const && (不可修改指向),const T&& 就是右值引用（加const了）
	{
		cout << "const r-value: " << t << endl;
	}
	template<typename T>
	void testForward(T && v)//当 左值 和 左值引用 传来，变为左值引用
	{
	    printValue(v); //已经命名，全是左值，即使参数是右值，右值引用
	    printValue(move(v));//move转换为右值，全是右值
	    printValue(forward<T>(v));//forward模板 当T为左值引用类型时，v将被转换为T类型的左值，其它都是右值
	    cout << endl;
	}

	int main(int argc, char* argv[])
	{
		//lvalue 是 locator value 的缩写，rvalue 是 read value 的缩写
		//左值是指存储在内存中、有明确存储地址（可取地址）的数据；
		//右值是指可以提供数据值的数据（不可取地址）； 右值引用（ R-value reference），标记为 &&


		int && a1 =10;
		//int && b=a1;//报错 a有名是左值引用 ，用 move
		int && b=move(a1);//对于list就不用复制了

		list<string> ls;
		ls.push_back("hello");
		ls.push_back("world");
		list<string> ls1 = ls; // 需要拷贝, 效率低
		list<string> ls2 = move(ls);

		Test   t1;
		Test   t2 =t1;// 需要拷贝，调用了复制构造函数

		Test  t00 = getTest();//GCC因为有赋值没有析构,但VC调用了Test(Test&& a)再调用析构

		Test t;
		Test x;
		//decltype(x) && v1 = t;          // error
		decltype(x) && v2 = move(t);    // 换 左值  到 右值引用,没有复制动作


//		Test & t31 =Test();   // error,右值不能给左值
		//Test & t32 =getConstTest();//右值不能给左值
		//Test & t32 =getTest();// 错误 ????



		Test && t11 = getTest();

		const Test& t22 = getTest();
		//常量左值引用是一个万能引用类型
		const Test& t33 = Test();
		const Test& t44 = x;

		{
			//auto && 要推算
			int x = 520, y = 1314;
			auto&& v1 = x;//v1是int&
			auto&& v2 = 250;
			auto&& v3 = v2;//v3是int&

			const int& c=10;
			const int&& d=10;
			auto && v4=c;//v4类型为 const int &,只一个&
			auto && v5=d;//v5类型为 const int &,只一个&
			auto && v6=&x;//v5类型为 int *&&

			//decltype(x)&& v3 = y;   // error,因decltype不用推算
			cout << "v1: " << v1 << ", v2: " << v2 << endl;
		}
		int a=10;
		printValueR(&a);

		printValue(10);// 到函数里类型为 int &&,右值引用
		printValue(a);//调用 一个&方法
		printValue(&a);// 到函数里类型为 int* &&,左值引用,里面要用*a才能取到值

		//T && 要推算
		testForward(520);//右值传过去
		int num = 1314;
		testForward(num);;//左值传过去
		testForward(forward<int>(num));//右值传过去，forward模板 当T为左值引用类型时，t将被转换为T类型的左值，其它都是右值
		testForward(forward<int&>(num));//左值引用传过去
		testForward(forward<int&&>(num));//右值传过去，forward模板 当T为左值引用类型时，t将被转换为T类型的左值，其它都是右值


		return 1;
	}
};
