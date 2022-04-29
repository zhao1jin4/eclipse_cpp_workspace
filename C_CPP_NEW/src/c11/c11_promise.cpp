
#include <iostream>
#include <thread>
#include <future>

using namespace std;

namespace c11_thread_promise{

	void TestFuture(promise<string> p){//如果参数形式为promise<string> & p,就要使用std:ref(p)传过来
		cout<<"sub thread begin wait"<<endl;
		this_thread::sleep_for(1s);
		p.set_value("calc value is 200");
		cout<<"sub thread after set value  "<<endl;
	}
	int asyncFunc(int a){
		cout<<"asyncFunc thread begin wait,thread id="<<this_thread::get_id()<<",a="<<a<<endl;
		this_thread::sleep_for(2s);//2s=duration,运算符重载了""s
		return 5;
	}
	int main(int argc, char *argv[])
	{
		cout<<"main thread  id="<<this_thread::get_id()<<endl;
		promise<string> p;
		auto future=p.get_future();
		cout<<"main thread start sub thread"<<endl;
		auto thread1=thread(TestFuture,move(p));//move转换为右值
		cout<<"main thread wait sub thread"<<endl;
		string res=future.get();//阻塞
		cout<<"main thread get  sub thread value"<<res<<endl;
		thread1.detach();


		//auto future1 = std::async(asyncFunc,20);//开线程，看源码launch::async|launch::deferred 两个由系统自动选择
		auto future1 = std::async(launch::deferred,asyncFunc,20);//deferred不会立即启动，而是在wait()或者get()时启动,还是使用调用者的线程做的

		future1.wait();//等待线程，不返回结果，future也有 wait_for  和 wait_until方法

		future_status status=future1.wait_for(std::chrono::seconds(1));
		if(status == future_status::timeout){
			cout<<"wait for is timeout"<<endl;
		}else if (status == future_status::ready){
			cout<<"wait for is  ready"<<endl;
		}else if (status == future_status::deferred){
			cout<<"wait for is  deferred"<<endl;
		}


		//int val=future1.get();//如不调用wait(),会阻塞,future是转移数据，不能调用两次get()
		//cout<<"async thread value"<<val<<endl;

		cout<<"future1.valid="<<future1.valid()<<endl;//1
		//std::shared_future<int> shared(move(future1));//move到右值,shared_feture是复制的，可多次读
		std::shared_future<int> shared=future1.share();
		cout<<"future1.valid="<<future1.valid()<<endl;//0
		cout<<"shared="<<shared.get()<<endl;
		cout<<"shared="<<shared.get()<<endl;
		return 0;
	};


}
