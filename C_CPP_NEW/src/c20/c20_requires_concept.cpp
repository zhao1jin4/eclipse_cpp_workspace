#include <iostream>


using namespace std;

namespace c20_requires_concept {


	//只可以匹配两个float参数传进来，不能是两个int(模板做类型限制)
	//floating_point 浮点,_v=value (std::enable_if_t 中_t=type)
	template<typename Float>
	auto myadd(const Float x,const Float y) requires std::is_floating_point_v<Float>{
		return x+y;
	}
	//--方式二
	template<typename T>
	concept floating_point=std::is_floating_point_v<T>;
	template<floating_point Float>
	auto myadd2(const Float x,const Float y) {
		return x+y;
	}
	//--方式三
	template<typename T>
	concept floating_point2=std::is_floating_point_v<T>;
	//				auto myadd3(const floating_point2 auto x,const floating_point2 auto  y) {//加auto,参数可以是不同类型小数
	floating_point2 auto myadd3(const floating_point2 auto x,const floating_point2 auto  y) {//返回也可修改
		return x+y;
	}


	template<typename FuncObj>
	auto use_func(FuncObj obj)
	{
		return obj();
	}
	template<typename FuncObj>
	auto use_func2(FuncObj obj)
		requires requires {&FuncObj:: operator();} //不能传 函数名 即 指向函数的指针
	{
		return obj();
	}

	template<typename T> concept has_call_operator=requires {&T:: operator();};//要以;结尾

	template<typename FuncObj>
	auto use_func3(FuncObj obj)
		requires  has_call_operator<FuncObj> //简化为使用concept
	{
		return obj();
	}
	int empty_func(){
		return 1;
	}


	//--<concepts> 头文件， 比模板好的是，只能用指定的类型，而不是所有的类型
	template<typename T>
	concept MyInt=same_as<T,int> ||same_as<T,long> ||same_as<T,long long>||same_as<T,unsigned int>||same_as<T,unsigned long>;
	template<MyInt T>
	T add(T a,T b){
		return a+b;
	}

	int main(int  argc, char* argv[])
	{

		myadd(3.1,4.1);
		myadd2(3.1,4.1);
		myadd3(1.5,1.6f);//可以是不同类型小数


		use_func([](){});
		use_func(empty_func);
		use_func2([](){});
		//use_func2(empty_func);//编译失败， 不匹配规则，不能传 函数名 即 指向函数的指针
		use_func3([](){});
		//use_func3(empty_func);//编译失败




		int res=add(2,3);//不能使用float,double

		return 1;
	}
}
