/*
#include <iostream>
#include <thread>
#include <barrier>

using namespace std;
namespace c20_thread_barrier{

	//类似Java CyclicBarrier
	void TestBar(int i,barrier<>*bar){
		cout<<"sub thread begin wait"<<endl;
	    this_thread::sleep_for(1s);
	    bar->wait(bar->arrive());

	}
	int main(int argc, char *argv[])
	{
		int count=3;
		barrier bar(count);
		for(int i=0;i<count;i++)
		{
			thread th(TestBar,i,&bar);
			th.detach();
		}
		getchar();
		return 0;
	};
}
*/
