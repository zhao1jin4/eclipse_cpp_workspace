#include <array>
#include <iostream>
#include <thread>
#include <barrier>
#include <concepts>
#include <vector>
#include <set>
#include <ranges>
#include <type_traits>
#include <algorithm>
#include <functional>
using namespace std;

namespace c20_new{

 	//类似Java CyclicBarrier
	void TestBar(int i,barrier<>*bar){
		cout<<"sub thread begin wait"<<endl;
	    this_thread::sleep_for(1s);
	    //bar->wait(bar->arrive());//当有3个线程时才开始同时执行
	    bar->arrive_and_wait();//合并两个函数
	    //也有 bar->arrive_and_drop(); 不常用
	    cout<<"sub thread do job at same time,thread_id="<<this_thread::get_id()<<endl;

	}
	class Person{
	public:
		Person(int age):age(age){};
		bool operator == (const Person & p){ //如重载了== 就不用重载!=
			return p.age == age;
		}
	private :
		int age;

	};


	struct rectangle{
		int weight : 3;//增加:3意思是3bit
		int height : 5 = 10;//可以加默认值
		//int thin ;

	};
	struct S{
		int i ;
		float f{};
		double d;
		S():d(1.0),i(2){};//warning上说d是最后初始化的,字段的最后，不受构造器的影响
	};

	void structParam(rectangle r)
	{
		cout<<r.weight<<endl;
	}
	struct Obj{
		std::array<int,3> data={1,2,3};//初始化列表
		const auto &get_data(){ //可加&
			return data;
		}

	};
	Obj get_obj(){
		return Obj{};
	}
	struct Box{
		int x ;
		int y;
	};
	template<typename T>
	struct BoxTemp{
			T x ;
			int y;
		};
	struct Base
	{
		//virtual int get_value()=0; 是纯虚函数
		//const成员函数才能被一个const类对象调用
		//[[nodiscard]] 指定函数的返回值不应被丢弃。 如果调用方丢弃返回值，则编译器会生成警告
		//constexpr virtual 函数 一起使用
		[[nodiscard]] constexpr virtual int get_value() const =0;
	};
	struct Derived:Base
	{
		[[nodiscard]] constexpr   int get_value()const override{
			//const成员函数不能使用非const变量
			return 5;
		}
	};
	struct Derived2:Base
	{
		[[nodiscard]] constexpr   int get_value()const override{
			return 10;
		}
	};
	struct NoConstructBox{
		int x ;
		int y;
		NoConstructBox()=delete; //防止有默认的构造
		NoConstructBox(int _x){
			x=_x;
		}
	};
	constexpr auto get_som_values(){
		const Derived d1;
		const Derived d2;
		const Derived d3;
		const Derived2 d4;
		const Derived2 d5;
		//<array>头文件C++11，模板第一是类型，第二个大小
		const std::array<const Base *,5> data{&d1,&d2,&d3,&d4,&d5};
		int total;
		for(auto * item:data)
		{
			total += item->get_value();
		}
		return total;
	}
	constexpr int const_dynamic(){
		if(std::is_constant_evaluated())//<type_traits>头文件,如果使用contexpr或const x= 接收这个函数值就是true
		//if constexpr(std::is_constant_evaluated())//是否在编译时间，条件一直成立
		{
			return 5;
		}else{
			return 10;
		}
	}
	template<typename Callable,typename ... Param> //模板可以动态数
	auto bind_values(Callable callable,Param ... param){
		//auto lamda = [=](){
		auto lamda = [callable=move(callable), ...param=move(param)](){//...放前面展开参数,多个值用逗号分隔
			return callable(param...);
		};
		return lamda;
	}
	int add(int one,int two){
		return one+two;
	}
	struct Man {
		int id;
		string name;
		auto operator <=> (const Man & m )const=default; //编译器生成比较，根据声明字段顺序比
		//如没有则 提示Man' is not derived from 'const std::optional<_Tp>'
	};

	constexpr auto get_value_inner(){
		int * i=new int{5};//没有delete
		return i;
	}
	constexpr auto get_value(){
		int * i=new int{}; //声明为constexpr类型的,如果接收这个函数的返回值使用constexpr，在这用new分配内存，就必须在constexpr的范围内(编译时间内)delete
		delete i;
		//嵌套函数里没有delete,后面也要补delete
		auto p=get_value_inner();
		auto val=*p;
		delete p;//这补的
		//如果先delete p;再auto val=*p;编译时就会报错

		return val;
//		return 1;
	}


	constexpr int const_method(){
		return 22;
	}
	void jthread_job(std::stop_token token){
		while(!token.stop_requested()){//判断停止消息
			std::this_thread::sleep_for(1ms);
			cout<<"jthread job"<<endl;
		}
	}
	enum struct MyColor{ //enum后可加struct
		red=1,
		green=2,
		blue=3,
	};
	string to_string_color(const MyColor c){
//		switch(c){
//		case MyColor::red:
//			return "red";
//		case MyColor::green:
//			return "green";
//		case MyColor::blue:
//			return "blue";
//		return "unkown";
//		}

		//新的方式,类似于import，可用于函数中
		using enum MyColor;
		switch(c){
		case red://省了前缀
			return "red";
		case green:
			return "green";
		case  blue:
			return "blue";
		return "unkown";
		}
	}
	namespace myns{
		using enum MyColor;//可用namespace中
	}
	struct WrapColor{
		using enum MyColor;//可用于struct中
		MyColor used=red;
	};
	consteval int sqr(int n){//consteval
		return n*n;
	}
	int main(int argc, char *argv[])
	{
		cout<<sizeof(rectangle)<<endl;

		rectangle r1{10,20};//老的方式,因设置:3,所以报warning溢出
		rectangle r{weight:10,height:20};//初始化,ISO不允许GNU设计的,C++20功能

		//S s{d:1.0,i:10};//报错,i和声明字段顺序不一样
		structParam({weight:23,height:10});//{}传参数转换为struct


		auto max_lamda=[]<typename T>(T x,T y){//lamda支持模板
			return x>y?x:y;
		};
		cout<<max_lamda(3,5)<<endl;


		std::array data{1,2,3};//<array>头文件，C++11,以前就有的
		auto total=0;
		for(std::size_t pos=0;const auto v: data){ //for : 循环，可以在前加语句
		 	total+=(v*pos);
			pos++;
		}
		//total=8
		for(const auto v: get_obj().get_data()){//可直接用，有&
			total+=v;
		}

		auto box1=Box{.x=1, .y=1};//designate 命名 ，属性前加.
		auto box2=Box{.x{2}, .y=1};
		//auto box3=Box{.x(3), .y=1}
		auto box4=Box{ //在结构体初始化时可以 属性= 后面值为lamda
			.x=[](){
				return 1;
			}(),
			.y=1
		};

		auto box5=BoxTemp<int>{
			.x=[](){
				return 1;
			}(),
			.y=1
		};


		auto int_ptr=make_unique<int>(20);
		auto printAddr=[](const auto &p){
			cout<<std::to_address(p)<<endl;//to_address转换为C的地址
		};
		printAddr(int_ptr);
		int num=3;
		printAddr(&num);
		auto ages=vector<int>{20,30};
		printAddr(ages.begin());

		auto simple_lamda=[]{return 5;};//没有参数时可以没有()
		auto simple_lamda2 = simple_lamda;//lamda可以复制
		decltype(simple_lamda)  simple_lamda3 ;//decltype可用于lamda上
		decltype([]{})  simple_lamda4 ;

		//--示例1
		auto file_clean =[](FILE * f){
			fclose(f);
			cout<<"the file closed"<<endl;
		};
		auto file_ptr=unique_ptr<FILE,decltype(file_clean)>(fopen("c:/tmp/a.txt","r"),file_clean);//decltype里可是lamda
		//--示例2
		//<set>头文件,第一个参数是初始化列表，第二参数比较器
		std::set myset{ {Box{1,2}},[](const auto &left ,const auto &right){
					return left.x>left.x;
				}
		 };
		//模板第一个参数元素类型，第二个比较器
		std::set<Box,decltype([](const auto &left ,const auto &right){
			return left.x>left.x;
		})> myset2 ;

		get_som_values();

		constexpr int dyn=const_dynamic();
		cout<<dyn<<endl;//5
		const int dyn1=const_dynamic();
		cout<<dyn1<<endl;//5
		int dyn2=const_dynamic();
		cout<<dyn2<<endl;//10,if constexpr(std::is_constant_evaluated()) 为5


		//NoConstructBox no_box{1,2};//C++11的功能,如有 NoConstructBox()=delete;这样报错
		NoConstructBox no_box{1};


		auto bind_func=bind_values(add,1,2);//如果个数不对，会编译报错
		cout<<"bind_func:"<<bind_func()<<endl;

		//bind_front 用来替代bind函数
		//auto mybind=std::bind_front(add,1); //<functional>头文件,可只传部分参数
		auto mybind=std::bind_front(&add,1); //&add
		cout<<"bind_front:"<<mybind(2)<<endl;//补齐其它的



		set<Man> peoples{{1,"lisi"},{2,"wang"}};//<set>头文件，set里的元素要有比较功能
		Man m1{1,"lisi"};
		Man m2{2,"wang"};
		cout<< "m1 == m2?" <<( m1 == m2 )<<endl;


		int val=get_value();
		constexpr int val2=get_value();//如函数内部用new，就必须在编译时间做delete


		constinit static auto i=4; //constinit 编译时初始化 ,加static 因为本地变量不能为const
		constinit static auto i1 = const_method();//如函数没 constexpr 会报错


		jthread t1(jthread_job);//jthread
		std::this_thread::sleep_for(10ms);
		t1.request_stop();//停止消息
		t1.join();

		//likely和unlikely(linux内核中有自带的宏定义)，我们可给编译器一种暗示，即该分支条件被满足的概率比较大或比较小。而编译器利用这一信息优化其机器指令，
		if(argc>1) [[unlikely]] //对应的有   [[likely]]
			cout<<"argc>1"<<endl;
		else  [[likely]]
			cout<<"argc<=1"<<endl;

		//consteval 类似于constexpr constinit


		MyColor use_color=myns::red;

		int res=sqr(100);//函数使用consteval,参数不能是变量
		int x=10;
		//res = sqr(x);//参数是变量错误



		cout<<"========ranges======"<<endl;
		//--<ranges> 头文件 像java stream api
		auto const ints = {0,1,2,3,4,5};
		auto even = [](int i) { return 0 == i % 2; };
		auto square = [](int i) { return i * i; };
		//老的方式,函数嵌套，第一个参数是输入
		//std::views::filter ,std::views::transform
		for (int i : std::views::transform(std::views::filter(ints, even), square)) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
		//管道当输入
		for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
			std::cout << i << ' ';
		}
		cout<<"========ranges  end======"<<endl;

		//--类似Java CyclicBarrier
		int count=3;
		barrier bar(count);
		for(int i=0;i<count;i++)
		{
			thread th(TestBar,i,&bar);
			th.detach();
		}



		Person p1{11},p2{22};
		cout<< (p1!=p2) <<endl;//如重载了== 就不用重载!= ,要加()
		cout<< (p1==p2) <<endl;




		//https://en.cppreference.com/w/cpp/language/coroutines
		//Coroutine 定义在 <coroutine> 头文件中

		//module 模块 import export  像JDK9

	    this_thread::sleep_for(1s);
		return 0;
	};
}


