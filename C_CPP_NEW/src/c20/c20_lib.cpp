#include <mutex>
#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <bitset>
#include <bit>
#include <numeric>
#include <numbers>
#include <cmath>
#include <iomanip>
#include <source_location>
using namespace std;

namespace c20_lib {

	constexpr auto mysort(auto data){
		std::sort(begin(data),end(data));//std::sort
		return data;
	}
	void log(const std::string_view message,  //string_view
	         const std::source_location location =
	               std::source_location::current())// <source_location>头文件
	{
	    std::cout << "file: "
	              << location.file_name() << "("
	              << location.line() << ":"
	              << location.column() << ") `"
	              << location.function_name() << "`: "
	              << message << '\n';
	}

	int main(int  argc, char* argv[])
	{
		constexpr auto sorted_data=mysort(std::array{20,44,52,78,65,44});
		static_assert(std::is_sorted(begin(sorted_data), end(sorted_data)));//std::is_sorted
		cout<<sorted_data[0]<<endl;


		//set排序的，不允许重复
		//multiset 排序的，允许重复
		multiset myset{1,3,4,5,6,4,3,2,1};
		cout<<myset.count(4)<<endl;//元素为4的有几个
		myset.find(4);
		myset.contains(4);//C++20方法


		cout<<"5的二进制1的个数为"<<std::bitset<32>(5).count()<<endl; //<bitset>头文件
		cout<<"3的二进制1的个数为(无符号整数) popcount 为"<< std::popcount(3u) <<endl; //<bit>头文件，只可是unsign 整数类型，数字后加u
		cout<<"5和7的中间值为"<<std::midpoint(5,7)<<endl;//<numeric>头文件中 ,5+7/2
		cout<<"int最大值为"<<std::numeric_limits<int>::max()<<endl;
		cout<<"int最大值-10的中间值为"<<std::midpoint(std::numeric_limits<int>::max(),std::numeric_limits<int>::max()-10)<<endl;//不会越界错误

		const int nums[]={1,2,3};
		std::array<int,3> myarray=std::to_array(nums);//std::to_array
		std::to_array("22");

		std::cout<<"pi     派的值为"<<std::setprecision (30)<<std::numbers::pi<<std::endl;//<numbers>头文件中的名称空间为 std::numbers
		std::cout<<"pi_v double派"<<std::setprecision (30)<<std::numbers::pi_v<long double><<std::endl;//发现值和上面的不一样，这个比下面的要准一点


		//throw std::logic_error("logic error");

		log("Hello world!");

		return 1;
	}
}
