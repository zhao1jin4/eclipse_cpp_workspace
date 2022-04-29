
#include <iostream>
using namespace std;

namespace c11_final_override
{

//-----------final override 关键字
struct B {
  virtual void f()  final; //const final
  virtual void f(int);
};

struct D : B {
  //void f() const;            // error: D::f attempts to override final B::f
  //void f(long) override;     // error: doesn't override anything
  void f(int) override;      // ok
};

struct E final {

};
//struct F: E { }; // error: deriving from final class


void g(int) {
	int x=0;
	cout<<x<<endl;
}
template <class T> void f() { g(T()); }


class Animal
{
public:
	virtual void walk(){
		cout<<"Animal walk"<<endl;
	}
};

class Human  final //不可被继承
			:public Animal{
public:
	 void walk() override  final //不可再被子类重写,必须是重写了父类的virtual函数,override可有可无(和final没有先后顺序)，易读
	 {
		cout<<"Human walk"<<endl;
	}
};


int main(int argc, char* argv[])
{

  f<int>();
  return 0;
}

}
