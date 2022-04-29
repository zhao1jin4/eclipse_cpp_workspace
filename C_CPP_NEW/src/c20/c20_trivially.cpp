#include <mutex>
#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>

#include <type_traits>
using namespace std;

namespace c20_trivially {

//----------1
	template<typename Contained>
	struct Optional{

		union { Contained data; };//union的特别用法,没有名字???
		//Contained data;

		bool initialized=false;

		constexpr Optional &operator=(Contained && data){
			this->data=std::move(data);//仿问data??
			initialized=true;
			return *this;
		}
		~Optional()=default;
		/*
		 //加这个 static_assert 失败
		~Optional(){
			if(initialized){
				data.~Contained();//仿问data?? 显示调用析构函数
			}
		}
		*/
	};

//----------2
	template<typename Type>
	struct Optional_nontrivial{
		~Optional_nontrivial(){
			static_cast<Type *>(this)->data.~Contained();//static_cast函数强转
		}
	};
	struct Optional_trivial{

	 };

	template<typename Contained>
	struct Optional2: std::conditional_t<std::is_trivially_destructible_v<Contained>,//用继承 conditional_t条件
										Optional_trivial,//条件成立时用
										Optional_nontrivial<Optional<Contained>>//条件不成立时用
										>
	{
		union { Contained data; };

		bool initialized=false;

		constexpr Optional2 &operator=(Contained && data){
			this->data=std::move(data);
			initialized=true;
			return *this;
		}

	};
	//--------3
	template<typename Contained>
	struct Optional3
	{
		union { Contained data; };

		bool initialized=false;

		constexpr Optional3 &operator=(Contained && data){
			this->data=std::move(data);
			initialized=true;
			return *this;
		}
		//新的,使用concept去约束 析构
		constexpr ~Optional3() requires( ! std::is_trivially_destructible_v<Contained>)
		{
			if(initialized){
				data.~Contained();
			}
		}
		constexpr ~Optional3()=default;
	};

	int main(int  argc, char* argv[])
	{
		Optional<int> obj;
		obj=5;

		//断言失败影响编译(如自己实现~Optional(){}就会失败)
		static_assert(std::is_trivially_destructible_v<Optional<int>>);//trivially 平凡地(即简单数据类型)，要<type_traits>头文件
		//static_assert(std::is_trivially_destructible_v<Optional<string>>);//失败，string是简单数据类型

		static_assert( std::is_trivially_destructible_v<Optional2<int>>);
		static_assert(!std::is_trivially_destructible_v<Optional2<string>>);

		static_assert( std::is_trivially_destructible_v<Optional3<int>>);
		static_assert(!std::is_trivially_destructible_v<Optional3<string>>);


		return 1;
	}
}
