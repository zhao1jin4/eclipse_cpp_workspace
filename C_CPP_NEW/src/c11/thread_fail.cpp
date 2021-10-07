#include <atomic>
#include <iostream>
#include <thread>
using namespace std;
namespace thread_fail{
	class MyInvoke{
		public:
		MyInvoke (){
			cout<<"MyInvoke contructor " <<endl;
		}

		 MyInvoke (MyInvoke & my){
				cout<<"MyInvoke copy contructor " <<endl;
			}

	  //源码中有thread(const thread&) = delete;
//		void operater()(){ //报错,不支持重载()？？？
//			cout<<"MyInvoke operater () " <<endl;
//		}
	};


	int main(int argc, char *argv[])
	{

		MyInvoke my;
//		thread  thread1(my);//报错,不支持重载()？？？


//	    std::string* p  = new std::string("Hello");
//	    data = 42;
//	    ptr.store(p, std::memory_order_release);


		return 0;
	};


}
