#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cstring>
#include <functional>
using namespace std;

namespace c11_smart_ptr{

	class Test
	{
	public:
		Test()
		{
			cout << "construct Test..." << endl;
		}
		Test(int x)
		{
			cout << "construct Test, x = " << x << endl;
		}
		Test(string str)
		{
			cout << "construct Test, str = " << str << endl;
		}
		~Test()
		{
			cout << "destruct Test ..." << endl;
		}
	};
	// 自定义删除器函数，释放int型内存
	void deleteIntPtr(int* p)
	{
		delete p;
		cout << "int 型内存被释放了...";
	}
	void sharePtr(){

		//构造函数初始化
		shared_ptr<int> ptr1(new int(520));//int 型的堆内存
		cout << "ptr1 引用计数: " << ptr1.use_count() << endl;//1

		//数组
		shared_ptr<char> ptr2(new char[12]);
		cout << "ptr2 " << ptr2.use_count() << endl;//1

		shared_ptr<int> ptr3;
		cout << "ptr3 " << ptr3.use_count() << endl;//0
		shared_ptr<int> ptr4(nullptr);
		cout << "ptr4 " << ptr4.use_count() << endl;//0

		int *p = new int;
		shared_ptr<int> p1(p);
		//shared_ptr<int> p2(p);// error, 编译不会报错, 运行会出错，即同一块内存，不可被两个管理
		shared_ptr<int> p2(p1);//另一个指针初始化
		cout << "p1 count " << p1.use_count() << endl;//2
		cout << "p2 count " << p2.use_count() << endl;//2
		shared_ptr<int> p3 = p1;//赋值初始化
		cout << "p1 count " << p1.use_count() << endl;//3
		cout << "p2 count " << p2.use_count() << endl;//3
		cout << "p3 count " << p3.use_count() << endl;//3
		std::shared_ptr<int>  p4 = std::move(p3); //p3转移给p4，另一个功能为转换为右值
	   // shared_ptr<int> p4(std::move(p3));//写法2
		cout << "p4 内存引用计数: " << p4.use_count() << endl;//3
		cout << "p3 内存引用计数: " << p3.use_count() << endl;//0

		{
		//make_shared 初始化
		  shared_ptr<int> ptr1 = make_shared<int>(520);
		  shared_ptr<Test> ptr2 = make_shared<Test>();//调用类的构造函数
		  shared_ptr<Test> ptr3 = make_shared<Test>(520);//调用类的构造函数的参数
		}
		{
			shared_ptr<int> ptr1 = make_shared<int>(520);
			shared_ptr<int> ptr2 = ptr1;
			cout << "ptr1引用计数: " << ptr1.use_count() << endl;
			cout << "ptr2引用计数: " << ptr2.use_count() << endl;
			ptr2.reset();//取消这个指针的引用
			cout << "ptr1引用计数: " << ptr1.use_count() << endl;
			cout << "ptr2引用计数: " << ptr2.use_count() << endl;

			shared_ptr<int> ptr5;
			ptr5.reset(new int(250));//初始化
			cout << "ptr5 引用计数: " << ptr5.use_count() << endl;

			//reset还有其它功能 ？？
		}
		int len = 128;
		shared_ptr<char> ptr(new char[len]);
		char* add = ptr.get();   // 得到指针的原始地址
		memset(add, 0, len);
		strcpy(add, "我!!!");
		cout << "string: " << add << endl;

		shared_ptr<int> pd1(new int(250), deleteIntPtr);//删除函数
		shared_ptr<int> pd2(new int[10], [](int* p) {delete[]p; });//删除数组
		shared_ptr<int> pd3(new int[10], default_delete<int[]>());//default_delete 删除数组
	}
	void myUniquePtr()
	{

		unique_ptr<int> ptr1(new int(10));
		//unique_ptr<int> ptr2 = ptr1;// error, 不允许将一个unique_ptr赋值给另一个unique_ptr

		unique_ptr<int> ptr2 = move(ptr1);// 通过转移所有权的方式初始化,同shared
		{
			unique_ptr<int> ptr1(new int(10));
			unique_ptr<int> ptr2 = move(ptr1);

			//cout << *ptr1.get() << endl;//error,unique_ptr没有use_count()
			cout << *ptr2.get() << endl;
			ptr1.reset();//解除对原始内存的管理
			ptr1.reset();//多次调用没问题
			ptr2.reset(new int(250));//重新指定智能指针管理的原始内存
			cout << *ptr2.get() << endl;
		}
		{
			using func_ptr = void(*)(int*);//删除函数的类型
			unique_ptr<int, func_ptr> ptr1(new int(10), [](int*p) {delete p; });
			//unique_ptr<int, func_ptr> ptr2(new int(10), [&](int*p) {delete p; });	// error
			unique_ptr<int, function<void(int*)>> ptr2(new int(10), [&](int*p) {delete p; });
		}
	}

	//共享指向this特殊用法
	struct Test2 :public enable_shared_from_this<Test2>
	{
	    shared_ptr<Test2> getSharedPtr()
	    {
	        //return shared_ptr<Test2>(this);//不能这样用,会析构两次
	        return shared_from_this();//配合 继承自  enable_shared_from_this<Test2>使用
	    }
	    ~Test2()
	    {
	        cout << "class2 Test is disstruct ..." << endl;
	    }
	};


	struct TA;
	struct TB;
	struct TA
	{
	    weak_ptr<TB> bptr;//如为shared_ptr,循环引用,内存不能释放
	    ~TA()
	    {
	        cout << "class TA is disstruct ..." << endl;
	    }
	};
	struct TB
	{
	    shared_ptr<TA> aptr;
	    ~TB()
	    {
	        cout << "class TB is disstruct ..." << endl;
	    }
	};
	void myWeakPtr()
	{
		shared_ptr<int> sp(new int);

		weak_ptr<int> wp1;
		weak_ptr<int> wp2(wp1);

		weak_ptr<int> wp3(sp);
		weak_ptr<int> wp4;
		wp4 = sp;
		weak_ptr<int> wp5;
		wp5 = wp3;

	    cout << "wp1: " << wp1.use_count() << endl;//0
		cout << "wp2: " << wp2.use_count() << endl;//0
		cout << "wp3: " << wp3.use_count() << endl;//1
		cout << "wp4: " << wp4.use_count() << endl;//1
		cout << "wp5: " << wp5.use_count() << endl;//1
		wp5.reset();
		//expired资源是否已经被释放
		cout << "2. weak " << (wp5.expired() ? "is" : "is not") << " expired" << endl;//is expired

		{
		    shared_ptr<int> sp1, sp2;
		    weak_ptr<int> wp;
		    sp1 = std::make_shared<int>(520);
		    wp = sp1;
		    //sp2 = wp.lock();//lock()取监测的 shared_ptr 对象，如新变量产生一个新的计数，2
		    //sp1 = wp.lock();//计数为1
		    cout << "use_count: " << wp.use_count() << endl;

		}

		//共享指向this特殊用法
		shared_ptr<Test2> sp1(new Test2);
		cout << "use_count: " << sp1.use_count() << endl;//1
		shared_ptr<Test2> sp2 = sp1->getSharedPtr();
		cout << "use_count: " << sp1.use_count() << endl;//2

		//循环引用
	    shared_ptr<TA> ap(new TA);
		shared_ptr<TB> bp(new TB);
		ap->bptr = bp;
		bp->aptr = ap;



	}
	int main(int argc, char* argv[])
	{

		//unique_ptr(计数永远为1) 、shared_ptr(引用计数)、weak_ptr （不会增加计数，监视shared_ptr）三种智能指针
		sharePtr();
		myUniquePtr();
		myWeakPtr();

		return 1;
	}
};
