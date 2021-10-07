

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <ratio>

using namespace std;

namespace cpp11new{


//-----------友元是模板
template<class W>
class Q
{
  static const int I = 2;
public:
  friend W;
};

struct B
{
  int ar[Q<B>::I];
};



//----模板默认值
template <class T=long>
void templateDefault(T t=123){
	cout<<t<<endl;
}



void f(int){
	cout<<"f int"<<endl;
} //#1
void f(char *){
	cout<<"f char"<<endl;
}//#2


constexpr int sumByNum(int num){
	int res=0;
	for(int i=0;i<num;i++)
		res+=i;
	return res;
}


int main(int argc, char *argv[])
{
	//C++03
    f(0); //调用的是哪个 f? 测试是int
    //C++11
    f(nullptr); //毫无疑问，调用的是 #2


   std::string s("hello");
	int m=int();
	std::string s1="hello";
	int a=5;

	int arr[4]={0,1,2,3};
	struct tm today={0};  //tm是一个已经定义的struct

	struct S {
		int x;
		S(): x(0){}//构造函数使用成员进行初始化：
	};


	long long my64;
	unsigned long long mypos64;
	char16_t cn='中';
	char32_t cn32='中';



	//int myint{5.0}; //从大double到int不可以
	double myint{5};
	//int myint3={5.0}; //从大double到int不可以
	double myint2={5};
	int pi(3.14);//可从大到小

	string longstr="<html> \
				</html>\
			";
	cout<<longstr.c_str()<<endl;//string用c_str(),显示的前面空格还是有的,输出并没有换行 每行加\来分隔
	//R
	string path=R"(c:\tmp\my.txt)"; //使用R
	cout<<path<<endl; //有没有c_str() 输出\t都是制表符

	string bodystr=R"(<body> 
				</body>
			)"; //输出有换行
	cout<<bodystr.c_str()<<endl;

	path=R"win(c:\tmp\my.txt)win"; //()前后的必须使用相同字符，只做备注使用
	cout<<path<<endl;


//	const double const_pi=3.14;
//	constexpr double two_pi=2*const_pi;//报错
//	int n=2;
//	constexpr double n_pi=n*const_pi;//报错
	constexpr double pi2=3.14*2;
	constexpr double pi3=pi2*2;
	//pi3=33;//不可修改
	constexpr int sum=sumByNum(5);//函数也要声明constexpr



	templateDefault("123");//如没有指定模板类型，可根据参数推算出为string

	{	//--string
	    string pi = "pi is " + to_string(3.1415926);
		string love = "love is " + to_string(5.20 + 13.14);
		cout << pi << endl;
		cout << love << endl;

		string str1 = "45";
		string str2 = "3.14159";
		string str3 = "9527 with words";
		string str4 = "words and 2";

		int myint1 = std::stoi(str1);
		float myint2 = std::stof(str2);
		int myint3 = std::stoi(str3);
		// 错误： 'std::invalid_argument'
		// int myint4 = std::stoi(str4);

	}


	return 1;
 }
struct A1
{
  A1()=default; //C++11
  virtual ~A1()=default; //C++11
};



//#include<stdio.h>//C老式的
//#include<cstdio>//C新式的





}//namespace
