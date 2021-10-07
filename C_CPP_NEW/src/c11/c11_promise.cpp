
#include <iostream>
#include <thread>
#include <future>

using namespace std;
namespace c11_thread_promise{
	void TestFuture(promise<string> p){
		cout<<"sub thread begin wait"<<endl;
		this_thread::sleep_for(1s);
		p.set_value("calc value is 200");
		cout<<"sub thread after set value  "<<endl;
	}
	int main(int argc, char *argv[])
	{

		promise<string> p;
		auto future=p.get_future();
		cout<<"main thread start sub thread"<<endl;
		auto thread1=thread(TestFuture,move(p));//move转换为右值
		cout<<"main thread wait sub thread"<<endl;
		string res=future.get();//阻塞
		cout<<"main thread get  sub thread value"<<res<<endl;
		thread1.detach();

		getchar();
		return 0;
	};


}
