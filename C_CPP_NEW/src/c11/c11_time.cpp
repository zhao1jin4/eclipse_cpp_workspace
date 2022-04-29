#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

namespace c11_time{

// https://subingwen.cn/cpp/chrono/#4-2-time-point-cast
	void f()
	{
		cout << "print 1000 stars ...." << endl;
		for (int i = 0; i < 1000; ++i)
		{
			cout << "*";
		}
		cout << endl;
	}

	int main(int argc, char* argv[])
	{

		{ //--头文件 <ratio>
			 ratio<1,1000 > millisecond;// 代表的是 1/1000 秒，也就是 1 毫秒
		}
		{ //--头文件 <chrono>  慢性的，长期的
		   chrono::hours h(1);                          // 一小时
			chrono::duration<int, ratio<1000>> ks(3);    // 3000 秒

			// chrono::duration<int, ratio<1000>> d3(3.5);  // error
			chrono::duration<double> dd(6.6);               // 6.6 秒
			 //看源码有 using seconds	= duration<_GLIBCXX_CHRONO_INT64_T>;

			// 使用小数表示时钟周期的次数
			chrono::duration<double, std::ratio<1, 30>> hz(3.5);//时钟周期为 1/30 秒，共有 3.5 个时钟周期，所以 hz 表示的时间间隔为 1/30*3.5 秒


			std::chrono::milliseconds ms{3};         // 3 毫秒
			std::chrono::microseconds us = 2*ms;     // 6000 微秒

			//count()周期数
			std::cout <<  "3 ms duration has " << ms.count() << " ticks\n" //MinGW不能Debug
					  <<  "6000 us duration has " << us.count() << " ticks\n"//MinGW不能Debug
					  <<  "3.5 hz duration has " << hz.count() << " ticks\n";

			chrono::minutes t1(10);
			chrono::seconds t2(60);
			chrono::seconds t3 = t1 - t2;//duration 时钟周期不相同的时候，会先统一成一种时钟，然后再进行算术运算
			cout << t3.count() << " second" << endl;
		}
		{
			using namespace std::chrono;
		  // 新纪元时间 1970.1.1 早08点
			system_clock::time_point epoch;

			duration<int, ratio<60*60*24>> day(1);
			// 新纪元1970.1.1时间 + 1天
			system_clock::time_point ppt(day);

			using dday = duration<int, ratio<60 * 60 * 24>>;
			// 新纪元1970.1.1时间 + 10天
			time_point<system_clock, dday> t(dday(10));

			// 系统当前时间
			system_clock::time_point today = system_clock::now();

			// 转换为time_t时间类型
			time_t tm = system_clock::to_time_t(today);
			cout << "今天的日期是:    " << ctime(&tm)<<endl;  // ctime 同  asctime (localtime (time)) 设置了当前时区

			time_t tm1 = system_clock::to_time_t(today+day);
			cout << "明天的日期是:    " << ctime(&tm1)<<endl;

			time_t tm2 = system_clock::to_time_t(epoch);
			cout << "新纪元时间:      " << ctime(&tm2)<<endl;

			time_t tm3 = system_clock::to_time_t(ppt);
			cout << "新纪元时间+1天:  " << ctime(&tm3)<<endl;

			time_t tm4 = system_clock::to_time_t(t);
			cout << "新纪元时间+10天: " << ctime(&tm4)<<endl;
		}
		{
			using namespace std::chrono;
			//steady_clock 相当于秒表，只要启动就会进行时间的累加，并且不能被修改，非常适合于进行耗时的统计。

			// 获取开始时间点
			steady_clock::time_point start = steady_clock::now();
			f();
			steady_clock::time_point last = steady_clock::now();
			// 计算差值
			auto dt = last - start;
			cout << "总共耗时: " << dt.count() << "纳秒" << endl;

			// 整数时长：要求 duration_cast
			auto int_ms = duration_cast<chrono::milliseconds>(dt);

			// 小数时长：不要求 duration_cast
			duration<double, ratio<1, 1000>> fp_ms = dt;
			cout << "f() took " << fp_ms.count() << " ms, "//在这 MinGW 不能debug??
				<< "or " << int_ms.count() << " whole milliseconds\n";
		}


		return 1;

	}
};
