#include <thread>
#include <iostream>
using namespace std;

void task01(){
    thread t([]{
        cout<<"子线程中执行"<<endl;
    });
    t.join();
}