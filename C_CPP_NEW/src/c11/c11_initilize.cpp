#include <iostream>
#include <vector>
#include <map>
using namespace std;
namespace c11_init{

	class Init {
	public:
		int num=1; //非静态的也可以了
		Init(int i){
		}
	};

	void funcInit(){
		int* b = new int[3] { 1, 2, 0 };//初始化
		int array[]{1,2,3};
		int array1[]={1,2,3};

	//	int* b1 = new int[] { 1, 2, 0 };//目前不行
	//	double d = double{ 1.0, 2.0  };//目前不行
	}
	class X
	{
		int a[4];
		public:
		  X() : a{1,2,3,4} {} //C++11, 初始化数组成员
	};

	class MyNumber
	{
	public:
	    MyNumber(const std::initializer_list<int> &v) {
	    	cout<<v.size()<<endl;
	        for (const auto &itm : v) {//新的遍历,复制出一个新的,只在第一次计算出长度,可加引用&，如不想被修改加const
	            mVec.push_back(itm);
	        }
	        //initializer_list的第二种遍历
	        for(auto it=v.begin();it!=v.end();++it)//
	        {
	        	cout<<*it<<endl;
	        }
	    }
	  void print() {
	    for (auto itm : mVec) {
	        std::cout << itm << " ";
	    }
	  }
	private:
	    std::vector<int> mVec;
	};
	int main(int argc, char* argv[])
	{
		vector<string> vs={ "first", "second", "third"};
		map<string,string> singers =    { {"Lady Gaga", "+1 (212) 555-7890"},
		                    {"Beyonce Knowles", "+1 (212) 555-0987"}};
		int* a = new int[3] { 1, 2, 0 }; //C++11 only

		//老的功能
		Init init3(1);//构造器
		Init init4=1;//自动调用 构造器,类型转换
		//新的功能
		Init init1{1};
		Init init2={1};


		{ //以前的作法
			int a[] = {0, 1, 2, 3};
			std::vector<int> vec(a, a+sizeof(a));

			//或
			std::vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);
		}
		std::vector<int> v = { 1, 2, 3, 4 };
		//initializer_list 初始化列表
		MyNumber myNum = { 1, 2, 3, 4 };
		myNum.print();  // 1 2 3 4


		//class（要无虚函数，无基数）,struct,union, 无私有或保护成员，都可用初始化列表
		struct Point{
			int x;
			long y;
			Point(int x){
			}
		} //p{200,200}
			p2{200};//有构造函数就只能调用构造函数了


		struct T1
		{
		    int x;
		    double y;
		private:
		    int z; //private的不能用初始化列表，
		};
		struct T2
		{
		    T1 t1;
		    long x1;
		    double y1;
		    int array[3]{1,2,3};
		};
		T2 t2{ {}, 520, 13.14 ,{4,5,6} };//{}表示不做初始化,数组初始化
		for(int i:t2.array){
			cout<<i<<endl;
		}
	}
};
