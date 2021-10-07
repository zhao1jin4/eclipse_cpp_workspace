#include <iostream>
#include <iomanip>
using namespace std;
namespace cpp_const
{

	class ConstClass
	{
	public:
		const int & size;
		static const int kind=10;//static是类的
		ConstClass():size(10)//const类型只能用初始化列表做初始化
		{

		}
		void overload_method() //可以和const重载
		{
			cout<<"  overload_method 不带const"<<endl;
		}
		void overload_method()  const//const要是类中的函数
		{
			cout<<"  overload_method 带const"<<endl;
			int a1,a2;
			int &b=a1;//b和a1 是同一个变量,b是个别名
			//int &b=a2;//重名错误,声明时初始化,

			int aa=29,bb=1001;
			cout<<aa<<setw(6)<<bb<<endl;
		}
	};

	int main(int argc, char* argv[])
	{
		//ConstClass::kind=8; //static的const也不能类外初始化

		ConstClass c;
		c.overload_method();


		const ConstClass c1;
		c1.overload_method();

		return 1;
	}

}

