#include <iostream>
using namespace std;
namespace move_contruct{

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

    //&&  移动构造函数,调用到的条件是一定要是临时对象(&&)，否则调用复制构造函数
   Test(Test&& a) : m_num(a.m_num) //m_num是浅复制，移动指针
   {
	   a.m_num = nullptr;//原指针为空，回收时不会回收那块公共内存
	   cout << "move construct:" << endl;
   }
    ~Test()
    {
        delete m_num;
        cout << "destruct Test class ..." << endl;
    }

    int* m_num;
};

Test getObj()
{
    Test t;
    return t;
}
Test getObj1()
{
    return Test();
}
int main(int argc, char *argv[]) //我测试的只 析构了一次
{
     Test t = getObj(); //测试并不能调到移动构造函数？？？ ,使用c++20就调用不到可能版本更新了
     Test && t1 = getObj(); //调不到移动构造函数？？？
     printf(" m_num addr:%p \n" , t1.m_num);
     Test && t2 = getObj1();
     printf(" m_num addr:%p \n" , t2.m_num);//地址不同啊？
	 Test t3=Test(); //调不到移动构造函数？？？
	 Test && t4=Test();//调不到移动构造函数？？？

	  Test x;
	  Test t5=x;//复制
    cout << "t.m_num: " << *t.m_num << endl;
    return 0;
};


}
