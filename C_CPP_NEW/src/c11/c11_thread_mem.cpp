#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <functional>

#include <atomic>
#include <mutex>
#include <condition_variable>
using namespace std;

namespace c11_thread_mem{

	class Test
	{
	public:
		Test() : m_num(new int(100))
		{
			cout << "construct" << endl;
		}

		Test(const Test& a) : m_num(new int(*a.m_num))
		{
			cout << "copy construct" << endl;
		}
		~Test()
		{
			cout << "~construct:" << endl;
			delete m_num;
		}

		int* m_num;
	};

	void thread_method(int age, string name, Test* obj)//参数不能使用引用 & ,即不能int & age,但可以指针*
	{
		printf(" thread id %d age address is %p\n",this_thread::get_id(),age);
		printf(" thread id %d name address is %p\n",this_thread::get_id(),name);
		printf(" thread id %d name = %s\n",this_thread::get_id(),*name.c_str());
		printf(" thread id %d obj is %d\n",this_thread::get_id(),*(obj->m_num));
		 //如果一个线程结束，如指向被回收，主线程再用就有问题(有类的析构函数，测试下来并没有被调用回收，没有析构)，
		int x=0;//CDT工具，C++11多线程debug不能显示源码??
		x++;
	}
	int main(int argc, char* argv[])
	{
		 char * name="lisi";
//		 std::string* name = new std::string("Hello");
		 printf("main thread name address is %p\n",name);

		 Test* obj=new Test();//但如果主线程先结束，子线程也结束（主线程的内存释放，子线程还继续访问的可能性有多大）
		 int age=20;
		 int &age1=age;

		 thread t1(thread_method, age1, name,obj);//参数传递是以复制方式，指针是地址
		 thread t2(thread_method, age1, name,obj);

		 t1.detach();
		 t2.detach();

		 this_thread::sleep_for(chrono::seconds(1));
//		 printf("main thread name is %s\n",name->c_str());
		 printf("main thread name is %s\n",name );
		 printf("main thread obj is %d\n",*(obj->m_num));
		 this_thread::sleep_for(chrono::seconds(1));
	}
};
