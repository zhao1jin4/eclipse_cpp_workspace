
#include<string>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;
namespace cpp_basic
{

	class Product
	{
	public :
		int id;
		string name;

		/*
		Product(Product &p)//复制构造函数的内部原理
		{
			id=p.id;
			name=p.name;
		}
		 */
	};

	class Order
	{
		public :
			int id;
			string name;

			operator int ()//不能有参数和返回值,把对象转换成int
			{
				return this->id;
			}
			Order()//默认构造函数
			{
				this->id=0;
				name="";
			}
			Order(int id)//无名对象
			{
				this->id=id;
				name="";
			}

			Order operator +(Order &o)//运算符重载
			{
				Order r;
				r.id = o.id + this->id;
				r.name = o.name + this->name;
				return r;
			}

			Order operator ++(int)//后置运算符重载,a++
			{
				this->id++;
				return (*this);
			}
	};
	class Parent
	{
	public:
		Parent(int age)
		{
			_age=age;
		}
		virtual ~Parent()
		{
			_age=0;
		}
		mutable int _age;//mutable  关键字
		void constFunc()const //可以仿问对象成员不可以修改,如果一定要修改,成员要声明为 mutable 关键字
		{
			_age=30;
		}
	};


	class Child;//声明
	class Neighboor
	{
	public:
		void readBirthday(Child c);
	};
	class Child:public Parent
	{
	private:
		string birthday;
		friend void Neighboor::readBirthday(Child);//friend可以仿问私有的,可以声明private,public
	public:
		string _name;
		Child(string name,int age):Parent(age), _name(name)
		{
		}
		virtual ~Child()
		{
			_name="";
		}

	};
	void Neighboor::readBirthday(Child c)
	{
		cout<<c.birthday<<endl;
	}


	void objectTest()
	{
		Product p;
		p.id=2;
		p.name="lisi";
		//Product p1(p);//自带的复制构造函数
		Product p1=p;//C++的写方法
		cout<<"id:"<<p1.id<<",name:"<<p1.name<<endl;


		//------------------
		Order order1(23);
		cout<<"对象转换成int:"<<order1+11<<endl;

		//------------------
		Order y= order1 + Order(55);//无名对象
		cout<<"id:"<<y.id<<",name:"<<y.name<<endl;
		y++;
		cout<<"id:"<<y.id<<",name:"<<y.name<<endl;
		//----特殊用法 1
			struct myclass {
			  int operator()(int a) {return a;}
			} myobject;
			int xy= myobject (0);

		//----特殊用法2
		class Tdate
		{
			public :
				int month;
				int & getm() //int & 引用，可以Tdate d,d.getm()=3可给函数赋值  只C++
				{
					return month;//中不能有对 month=20;的操作,否则赋值无效,必须返回类的属性
				}
		};

		Tdate t;
		t.getm()=4;//赋值
		cout<<t.getm()<<endl;
		cout<<t.month<<endl;

		//---

	}

	void typeid_typeof()
	{
		//VC编译器的显示结果比MinGW要好很多

		int found;
		typeof(found) a;//声明一个变量a，和found是同一个类型
		a=123;

		int * pi;
		  cout << " pi is: " << typeid(pi).name() << endl;
		  cout << "*pi is: " << typeid(*pi).name() << endl << endl;

		vector<string> collection;
		cout<<"typeid的值:"<<typeid(collection).name()<<endl;//要 #include <typeinfo>
		cout << typeid(int).name() << endl;
		cout << typeid(a).name() << endl;

		if (typeid(int) == typeid(a))
		   cout << "typeid(int) = typeid(a)" << endl;

		struct Base {};
		struct Derived : Base {};
		struct Poly_Base {virtual void Member(){}};
		struct Poly_Derived: Poly_Base {};
		// non-polymorphic types:
		  Derived derived;
		  Base* pbase = &derived;
		  cout << "derived is: " << typeid(derived).name() << endl;
		  cout << " *pbase is: " << typeid(*pbase).name() << endl;
		  cout << boolalpha << "same type? ";
		  cout << ( typeid(derived)==typeid(*pbase) ) << endl << endl;

		  // polymorphic types:
		  Poly_Derived polyderived;
		  Poly_Base* ppolybase = &polyderived;
		  cout << "polyderived is: " << typeid(polyderived).name() << endl;
		  cout << " *ppolybase is: " << typeid(*ppolybase).name() << endl;
		  cout << boolalpha << "same type? ";
		  cout << ( typeid(polyderived)==typeid(*ppolybase) ) << endl << endl;
	}



	void myunexpected () {
	  cerr << "unexpected called\n";
	  throw 0;
	}
	void myfunction () throw () {//c++17 不能在throw()里面加int等
	  throw  0.32;
	}

	inline void cpp_tool()//inline关键字
	{

		class Polymorphic {virtual void Member(){}};
		try
		{
			Polymorphic * pb = 0;
			typeid(*pb);  // throws a bad_typeid exception
		}
		catch (exception& e)
		{
			cerr << "exception caught: " << e.what() << endl;
		}

	  set_unexpected (myunexpected);//某个函数出现异常，而该异常未被列到异常列表，则myunexpected函数被系统自动调用。
	  try {
		  myfunction();
		}
	  catch (int) { cerr << "caught int\n"; }
	  catch (...) { cerr << "caught other exception \n"; }


	  cout << boolalpha;
	   cout << "Minimum value for int: " << numeric_limits<int>::min() << endl;
	   cout << "Maximum value for int: " << numeric_limits<int>::max() << endl;
	   cout << "int is signed: " << numeric_limits<int>::is_signed << endl;
	   cout << "Non-sign bits in int: " << numeric_limits<int>::digits << endl;


	}
	void testCast()
	{
		struct B1{
			    virtual ~B1(){}
			};
		struct B2{
			virtual ~B2(){}
		};
		struct D1 : B1, B2{};
		D1 d;
		B1* pb1 = &d;
		B2* pb2 = dynamic_cast<B2*>(pb1);//L1
		//B2* pb22 = static_cast<B2*>(pb1);  //编译报错


		//const_cast  也是关键字
		int i=4;
		const int& cref_i = i;
		const_cast<int&>(cref_i) = 4; //可以修改,是不同的变量



	}
	void newPointerArray()
	{

		int* b = new int[3] { 1, 2, 0 };//一维数组初始化
		for (int i = 0;i < 3;i++)
		{
			cout<<setw(10)<<b[i]<<endl;//iomanip
		}
		delete []b;


		 //二维数组的创建8行10列
		int(*p) = new int[80];
			int(*px)[10] = (int(*)[10])p;
			int data = 0;
			for (int i = 0;i < 8;i++)
			{
				for (int j = 0;j < 10;j++)
				{
					px[i][j] = data++;
					cout << px[i][j]<<" ";
				}
				cout << endl;
			}
			delete []p;



			//声明了一个二维数组，它的有2列，行数还不确定。
				int **a = new int*[2];
				//这个二维数组的列数确定了是5；
				for (int i = 0; i < 2; i++)
				{
					a[i] = new int[5];
				}
				//下面是赋值；
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						a[i][j] = i*5+j + 1;
					}
				}
				//下面是读取操作；
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						cout << " " << a[i][j];
					}
					cout << endl;
				}
				//下面是从对内存删除操作；
				for (int i = 0; i < 2; i++)
				{
					delete[] a[i];
				}
				delete[] a;
	}

	//int main(int argc,char* argv[] )
	int main(int argc,char **argv)
	{
		//objectTest();
		//cpp_tool();

		//typeid_typeof();
		//testCast();

		//newPointerArray();

		return 1;
	}


}







