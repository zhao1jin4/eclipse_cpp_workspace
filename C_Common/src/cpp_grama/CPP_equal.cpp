#include <iostream>
using namespace std;

namespace cpp_equal
{
	class Tdate
	{
		public :
			int month;
			int & getm() //int & 引用，可以Tdate d,d.getm()=3可给函数赋值  只C++
			{
				month=20;
				return month;
			}
	};
	int main(int argc, char* argv[])
	{
		Tdate t;
		t.getm()=4;//赋值
		cout<<t.getm()<<endl;
		cout<<t.month<<endl;
		return 1;
	}
}
