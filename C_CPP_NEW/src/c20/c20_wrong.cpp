#include <mutex>
#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>

//#include <type_traits>
using namespace std;

namespace c20_wrong {

//	template<typename Float ,
//			typename= std::enable_if_t<std::is_floating_point_v<Float>> //_v表示value,_t表示type
//			>
//	auto myadd(const Float x,const Float y)  {
//		return x+y;
//	}

//----

/*
	 constexpr auto get_value(){
		 return std::vector<int>{};//虽然没有new，但也要回收？？没办法回收？？
	 }
	 constexpr auto get_size(){
		 return get_value().size();
	 }
	 template<std::size_t Size>//template还可以不是typename或class
	 constexpr auto populate_data(){
		 auto value=get_value();
		 std::array<int,Size>data; //使用特别模板
		 std::copy(begin(value),end(value),begin(data));//std::copy
		 return data;
	 }
*/
//---
	/*
	const int my_lock(){
		constinit static std::mutex my_mutex;//这报错
		std::scoped_lock l(my_mutex);//  <mutex>头文件
		constinit static auto value=4;
		++value;
		return value;
	}
	*/
//----
	struct [[nodiscard("struct no receive value^^^")]]  NoDis{ //函数调用后的返回这个struct ,也要有接收值，否则warning ,[[nodiscard]]也可放struct前面

		[[nodiscard]]  NoDis(int){
		 }
	};
	NoDis get_no_dis(){
		return NoDis(3);
	}
	void log();
	int main(int  argc, char* argv[])
	{


		//--以下两行是错的
//		constexpr auto size=get_size();
//		constexpr auto val=populate_data<size>();//特别模板使用
		 //--


		//NoDis(2);
		get_no_dis();//这没有接收有warning
		//NoDis s=get_no_dis();


		//using namesapce std;也不行？？ 找不到M_PI
		//std::cout<<"派的值为"<<std::setprecision (9)<<M_PI<<std::endl;//<cmath>头文件中的M_PI,setprecision是<iomanip>头文件中


		std::vector<int> scores{66,77,88};
		cout<<scores[log,2]<<endl;//逗号分隔数组，warning提示过时,返回下标为2的元素

		return 1;
	}
}
