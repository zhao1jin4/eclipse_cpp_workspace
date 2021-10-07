#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

namespace c11_using{
		// 模板别名
		template <class T> using Ptr = T*;
		Ptr<int> ip;  // decltype(ip) is int*

		//Map的值是变类型的，老的方式
		template <typename T>
		struct  MyMap{
			typedef map<int,T> mapType;
		};
		MyMap<int>::mapType map1;
		MyMap<double>::mapType map2;

		//Map的值是变类型的，新的方式
		template <typename T>
		using MMap=map<int,T>;
	int main(int argc, char* argv[])
	{

		using typeint=int; //using 别名，像typedef
		typeint aliseInt=3;

		typedef int (*funcptr)(int,int);
		using  funptr1=int(*)(int,int);//using可读性好


	}
};
