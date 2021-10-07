#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <functional>

#include <atomic>
#include <mutex>
#include <condition_variable>
using namespace std;

namespace c11_thread{


	void func(int num, string str)
	{
		for (int i = 0; i < 4; ++i)
		{
			cout << "子线程: i = " << i << "num: "
				 << num << ", str: " << str << endl;

//			auto now = chrono::system_clock::now();
//			chrono::seconds sec(1);
//			this_thread::sleep_until(now + sec);//time_point类型

			// sleep_for()： duration 类型

			this_thread::yield();

		}
	}
	void func1()
	{
		for (int i = 0; i < 10; ++i)
		{
			cout << "子线程: i = " << i << endl;
		}
	}
	void myJoinDetachSleep(){
		cout << "主线程的线程ID: " << this_thread::get_id() << endl; //当前线程ID, this_thread 名称空间
		thread t(func, 520, "you");
		thread t1(func1);
		cout << "线程t 的线程ID: " << t.get_id() << endl;
		cout << "线程t1的线程ID: " << t1.get_id() << endl;
		 //t.join();//如还没执行完毕，主线程阻塞
		 //t1.join();
		 t.detach();//不会阻塞,分离之后，在主线程退出之前，它可以脱离主线程继续独立的运行 ,主线程退出也会一并销毁创建出的所有子线程
		 t1.detach();

		 {
			thread t;
			cout << "before starting, joinable: " << t.joinable() << endl;//0
			t = thread(func1);
			cout << "after starting, joinable: " << t.joinable() << endl;//1
			t.join();
			cout << "after joining, joinable: " << t.joinable() << endl;//0
		 }

	   int num = thread::hardware_concurrency();
	   cout << "CPU 核数: " << num << endl;
	}

	once_flag g_flag;
	void do_once(int a, string b)
	{
	    cout << "name: " << b << ", age: " << a << endl;
	}


	int g_num = 0;  // 为 g_num_mutex 所保护
	mutex g_num_mutex;
	//timed_mutex g_num_mutex;//timed_mutex 有 try_lock_for() 阻塞一定的时间长度和 try_lock_until()阻塞到某一个指定的时间点

	void do_something(int age, string name)
	{
	    static int num = 1;
	    call_once(g_flag, do_once, age, name);//只调用一次函数do_once，后面是参数,测试下来多数是第一个进入的线程执行
	    cout << "do_something() function num = " << num++ << endl;

	    g_num_mutex.lock();
	   // g_num_mutex.try_lock();//不阻塞

	   //chrono::seconds timeout(1);
	   //if (g_num_mutex.try_lock_for(timeout)){}

	    for (int i = 0; i < 3; ++i)
		{
			++g_num;
			cout << " g_num = " << g_num << endl;
		}
	    g_num_mutex.unlock();


		for (int i = 0; i < 3; ++i)
		{
		  //使用哨兵锁管理互斥锁 lock_guard  构造时自动锁，退出作用域析构时自动解锁
		  lock_guard<mutex> lock(g_num_mutex);
		  ++g_num;
		  cout << " lock_guard =  " << g_num << endl;
		  this_thread::sleep_for(chrono::seconds(1));
		}



	}
	void myMutex( )
	{

		 thread t3(do_something, 19, "luffy");
		 thread t1(do_something, 20, "ace");
		 thread t2(do_something, 20, "sabo");
		 t1.detach();
		 t2.detach();
		 t3.detach();
	}


	struct Calculate
	{
	    Calculate() : m_i(6) {}

	    void mul(int x)
	    {
	        lock_guard<recursive_mutex> locker(m_mutex);
	        m_i *= x;
	    }

	    void div(int x)
	    {
	        lock_guard<recursive_mutex> locker(m_mutex);
	        m_i /= x;
	    }

	    void both(int x, int y)
	    {
	        lock_guard<recursive_mutex> locker(m_mutex);
	        mul(x);
	        div(y);
	    }

	    int m_i;
	    recursive_mutex  m_mutex;//recursive_mutex 允许同一线程多次获得互斥锁,可递归调用,建议少用,转换非递归
	};


	class Obj{
	public:
		Obj(){
			cout<<"Obj constructor"<<endl;
		}
		Obj(int i):m_i(i){//整数转换为类
			cout<<"Obj conver from  m_i="<<m_i<<",thread id="<<this_thread::get_id()<<endl;
		}
		Obj(Obj & o ):m_i(o.m_i){
			cout<<"Obj copy constructor m_i="<<m_i<<",thread id="<<this_thread::get_id()<<endl;
		}
		~Obj(){
			cout<<"Obj deconstructor  m_i="<<m_i<<",thread id="<<this_thread::get_id()<<endl;
		}
		int m_i=0;
		static void thread_work_ptr( unique_ptr<int> ptr){
			ptr.reset(new int(250));//重新指定智能指针管理的原始内存
		}
	};
	void myPrint(const int & i,//如用&,要加const(&int是复制，地址不同)
			const char * mychar,//如用* 要用const(编译报错信息很难识别原因),如主线程提前结束空间释放，如子线程退出前就可能会有问题
			string mystr,
			const Obj &obj,
			Obj &obj1,
			const Obj * obj2
	)
	{
		cout<<"obj.m_id="<<obj.m_i<<endl;
		obj1.m_i=30;
		cout<<"obj2.m_id="<<(*obj2).m_i<<endl;

		cout<<"MyPrint i="<<i<<endl;
		cout<<"mychar="<< mychar<<endl;//不安全
		cout<<"mystr="<<mystr.c_str()<<endl;

	}
	int main(int argc, char* argv[])
	{

	   //myJoinDetachSleep();
	   myMutex( );
	   this_thread::sleep_for(chrono::seconds(5));


	   Calculate cal;
	   cal.both(6, 3);


	   //--atomic 一个struct

		atomic<int>   m_value(0);
		m_value=20; //重载了=
		m_value++; //重载了++

		//通过 store() 和 load() 来读写原子对象内部的原始数据。
		m_value.store(30);
		//m_value.store(40, std::memory_order_release);
		int res=m_value.load();

		//----
	   int myvar=30;
	   char mychar[] ="this is my char array";
	   int myobjInt=3;

	   cout<<"main thread id="<<this_thread::get_id()<<endl;
	   Obj obj(10);
	   Obj obj1(20);
	   thread t(myPrint,myvar,mychar,//指针不安全
			   string(mychar),//mychar[]到string是稳式转换，是先启动子线程再转换的，有可能主线已经结束，解决方法string(mychar)
			   myobjInt, //myobjInt 整数 转换  ,根据日志发现在转换是在子线程中做的
			   std::ref(obj1),//传递引用
			   &obj //参数只能用const Obj* obj ,不能用const Obj &obj
	   );
	   t.detach();
	   cout<<obj1.m_i<<endl;//被子线程修改过



	   unique_ptr<int> p1(new int(10));
	   //类中的方法，要是static,不能是某个对象的方法
	   thread t1(Obj::thread_work_ptr,std::move(p1));// 传能指针用move


	   return 1;
	}
};
