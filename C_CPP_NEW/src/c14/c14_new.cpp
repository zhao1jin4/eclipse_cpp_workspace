#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <memory>
#include <shared_mutex>
#include <utility>
#include <tuple>
using namespace std;

namespace c14_new
{

	struct Vec3
	{
		int x, y, z;
		// C++20 起不再需要以下构造函数
		Vec3(int x = 0, int y = 0, int z = 0) noexcept : x(x), y(y), z(z) { } //noexcept

		//运算符重载了<<
//		friend std::ostream& operator<<(std::ostream& os, const Vec3& v)
//		{
//			return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}';
//		}
	};

	auto square(double side){ //支持返回auto,对地复杂的模板类型，方便很多
		return side*side;
	}

	//windows下CDT环境， constexpr不能放main函数中，会导致不能运行,必须重启CDT才可？？,为何c++11_new.cpp文件中sumByNum是好的？？
	constexpr double pi=3.14;
	constexpr double two_pai=2*pi;//编译时确定值，而不是运行时
	/*
	//windows下CDT环境，constexpr函数不能开，会导致不能运行,必须重启CDT才可？？,为何c++11_new.cpp文件中sumByNum是好的？？
	constexpr int fib(int num){ //constexpr 表在函数上,编译时运行
		if(num==1)
			return 1;
		if(num==0)
			return 0;
		return fib(num-2)+fib(num-1);
	}
	*/
	template<typename T>
	constexpr T pi_type=T(3.14);//模板可以定义变量

	template<typename M>
	constexpr M max_num=M(1000);

	template<> //钻石语法,指定不同的值
	constexpr char max_num<char>('Z');

	[[deprecated("this is should not use ,we recommend use others")]]//编译时出这个warning信息
	void oldFunc(){
		cout<<"oldFunc"<<endl;
	}
	class Cat{
	public:
		Cat(){
			cout<<"contructor"<<endl;

		}
		~Cat(){
			cout<<"de contructor"<<endl;
		}
		int m_age=20;

	};
	int main(int argc, char* argv[])
	{

		int bin = 0b101010; //前缀0b或0B开头表示二进制
		int bin1 = 0B101010;

		int million=1'000'000;//千位分隔
		int million2=1'00'0'000;//随意位置
		cout<< (million==million2 )<<endl;


		//static_assert(fib(10)==55,"unexpected num."); //如果计算值不对，就会编译时报错，编译时运行

		cout<<pi_type<int><<endl;
		cout<<max_num<float><<endl;
		cout<<max_num<char><<endl;

//		int *abc=nullptr;
		int n{64};
		string s{"init method"};
//		delete []p; 后最好p=nullptr

		oldFunc();



		 //智能指针的增强make_unique，要加<memory>头文件
		 auto pcat=make_unique<Cat>();//返回类型为unique_ptr，自动调用构造，结束时自动析构
		 //现在c++ 大多数情况不需要new和delete
		 auto p = make_unique<double[]>(10);//指向 10元素的double数组 的指针

		 auto second=1s;//1s=1秒
		 auto hour=1h;
		 auto minute=1min;
		 auto millsecond=1ms;

		 auto hello="world";//类型为const char *
		 auto hellos="world"s;//s类型为string

		 chrono::milliseconds ten_sencond=10s;//做函数参数比int要好
		 cout<<ten_sencond.count()<<endl;
		 auto plus_sencond=ten_sencond+second;//重载了+，结果为单位小的
		 cout<<plus_sencond.count()<<endl;


		 std::pair point{2,5}; //pair 只可两个元素，模板可有可无
		 std::pair<double,string> point2(2.2,"ss");
		 cout<<point.first<<point.second<<endl;

		 std::tuple  student3(10,"lisi",89.5);//要<tuple>头文件,tuple可多个元素
		 tuple<int,string> student2(10,"lisi");//也可两个元素
		 int id= std::get<0>(student2);
		 string name=std::get<string>(student2);// 如只有一个string类型才可以这样用
		 cout<<id<<name<<endl;


		auto myAutoFunc = [](auto x, auto y) {return x + y;}; //可以参数是auto,返回值也是auto,不会出错
		cout<<"myAutoFunc="<<myAutoFunc(2,3)<<endl;
		auto myAutoFuncString = [](auto const& x, auto const& y) {return x + y;};//可加const&
		cout<<"myAutoFuncString="<<myAutoFuncString("abc"s,"def"s)<<endl;

		int a = 123;
		auto f = [a,b=10] { cout << a+b << endl; };//lamda初始值
		f();


		auto pNum=make_unique<int>(64);
		auto f2=[u{move(pNum)}](int a){//unique_ptr移动
		//auto f2=[u =move(pNum)](int a){//写法2
			cout<<(*u)<<a<<endl;
		};
		f2(20);



		//--------
		std::unique_ptr<int> ptr(new int(10));
		auto lambda = [value = std::move(ptr)] {return *value;};//[]里可以做赋值
		cout<<"lambda="<<lambda()<<endl;

		int x = 4;
		auto y = [&r = x, x = x+1]()->int {//r前加&才可修改，没指定类型。先执行逗号前，再执行逗号后
			//第一次 r=4,x=5
			r += 2;
			return x+2;
		 }();  // Updates ::x to 6, and initializes y to 7.
		 //结束时为什么x是6？？




		  /* pNums = make_unique<vector<int>>(nums);
			//...
		    auto a = [ptr = move(pNums)]()
			{
			   // use ptr
			};
		     */
//		int count=3;
//		constexpr string grade = if(count>10)?"A":"B";//constexpr后可加if,switch,区间的for





		 // 使用默认构造函数。
		std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();//make_unique函数产生unique_ptr
		// 使用匹配这些参数的构造函数
		std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2);
		// 创建指向 5 个元素数组的 unique_ptr
		std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);

		std::shared_timed_mutex my_share_mutex1; //定义在  <shared_mutex> 头文件中
		std::shared_mutex  my_share_lock1;


		 std::integer_sequence<unsigned, 9, 2, 5, 1, 9, 1, 6>{}; //定义在<utility>头文件中


		return 1;
	}

};


