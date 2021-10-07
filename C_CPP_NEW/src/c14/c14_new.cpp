#include <iostream>
#include <string>
#include <list>
#include <memory>

using namespace std;

namespace c14_new
{

	int main(int argc, char* argv[])
	{


		int bin = 0b101010; //前缀0b或0B开头表示二进制
		int bin1 = 0B101010;


		auto myAutoFunc = [](auto x, auto y) {return x + y;}; //可以参数是auto,返回值也是auto,不会出错
		//auto myAutoFunc = [](int x, int y) {return x + y;};

		std::unique_ptr<int> ptr(new int(10));
		auto lambda = [value = std::move(ptr)] {return *value;};


		int x = 4;
		auto y = [&r = x, x = x+1]()->int {//r前加&才可修改，没指定类型，先执行前，号前再执行后
			//第一次 r=4,x=5
			r += 2;
			return x+2;
		 }();  // Updates ::x to 6, and initializes y to 7.
		 	 //结束时为什么x是6？？
		/*

		pNums = make_unique<vector<int>>(nums);
			//...
		    auto a = [ptr = move(pNums)]()
			{
			   // use ptr
			};
		    */
		//		int count=3;
		//		constexpr string grade = if(count>10)?"A":"B";//constexpr后可加if,switch,区间的for




		return 1;
	}
};


