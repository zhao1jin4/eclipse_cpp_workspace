#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

namespace c11_auto{

	class ClassInt{
	public:
		static int get(){
			return 22;
		}
	};
	class ClassString{
	public:
		static string get(){
			return "hello中";
		}
	};


	template<class T> void printAuto()
	{
		auto res=T::get(); //auto动态类型
		cout<<res<<endl;
	}
	template<class T,class U> auto  addAuto(T a,U b) -> decltype(a+b) //返回类型是auto,通过decltype计算出，后加-> (返回类型不能是decltype因还不知道模板类型)
	{
		 return a+b;
	}
	void myAuto(){

		auto x=0; //0 是 int 类型，所以 x 也是 int 类型
		auto c='a'; //char
		auto d=0.5; //double
		auto national_debt=14400000000000LL;//long long
		auto& ref=d;//ref是d的别名
		ref=33;
		auto* ptr=&d;
		auto  ptr1=&d;

		const auto pi =3.14;
		auto p2=pi; //不能带const类型，是double类型

		volatile int tickets=10;
		auto tickets2 =tickets;//不能带volatile类型，是int类型


		//函数参数不能是auto
		//auto myarray[]={1,3,4};//auto不可初始化数组
		 int myarray[]={1,3,4};
		 auto youArray=myarray;//已经初始化的可以
		//vector<auto> myv=vi; //auto不用于替代模板

		 map<int,string> mymap;
		 mymap.insert(make_pair(1,"one"));//make_pair
		 //map<int,string>::iterator map_iter=mymap.begin() ;//非常长，用auto简单
		 auto map_iter=mymap.begin();
		 for (; map_iter != mymap.end(); map_iter++ )
			 cout << (*map_iter).first << " => " << (*map_iter).second << endl;

		 printAuto<ClassInt>();
		 printAuto<ClassString>();
		 auto res=addAuto(100,0.8);//double
		 auto res2=addAuto(100L,(short)20);//long

		 //final 关键字放在函数后面，并函数只可是类的，必须是重写了父类的virtual函数，表示不可再被子类重写
		 //final 关键字放在类后面 表示不可被继承
		 list<list<string>> l;// 其中的 >> ，原来中间必须有空格 "> >",现在可没有空格
	}
	class C
	{
	   //auto x=3.14; //auto不能用于类的非静态成员初始化
	   static constexpr auto num=3.14;//必须是static  constexpr

	   public:
		   C();
	};


	int main(int argc, char* argv[])
	{
		 myAuto();

		 return 0;
	}
};
