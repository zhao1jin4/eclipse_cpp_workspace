#include <string.h>
namespace c11_contructor{

	class Parent {
	public:
		int num=1;
		Parent():Parent(0)//构造器相互调用
		{

		}
		Parent(int i){
			this->num=i;
		}

	};
	class Child:public Parent{
	public :
		/*
		Child(int i) :Parent(i)//调用另一构造函数
		{
			//Parent(i);//这报错，i shadows a parameter 形参重定义？
		}
		*/
		using Parent::Parent; //就把父类所有的构造函数继承下来
	};

	struct A {
	  A(int);
	  A(): A(42) { } // delegate to the A(int) constructor
	};


	int main(int argc, char* argv[])
	{
		Child c(20);
		 return 0;
	}
};
