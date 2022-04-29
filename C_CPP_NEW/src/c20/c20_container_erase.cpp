#include <iostream> 
#include <vector> 
#include <algorithm>

using namespace std;

namespace c20_container_erase{

void print_container(const std::vector<int>& c)
{
//    for (int i : c) {
//        std::cout << i << " ";
//    }
    //--方式二
    for ( auto it=c.begin() ; it != c.end(); it++ )
	{
		cout << " " << *it;
	}

     std::cout << '\n';
}
int main(int argc, char **argv) {
	{
		 std::string str1 = "Text with some   spaces";

		auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');

		// The spaces are removed from the string only logically.
		// Note, we use view, the original string is still not shrunk:
		std::cout << std::string_view(str1.begin(), noSpaceEnd)
				  << " size: " << str1.size() << '\n';

		str1.erase(noSpaceEnd, str1.end());

		// The spaces are removed from the string physically.
		std::cout << str1 << " size: " << str1.size() << '\n';

		std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
		str2.erase(std::remove_if(str2.begin(),
								  str2.end(),
								  [](unsigned char x){return std::isspace(x);}),
				   str2.end());
		std::cout << str2 << '\n';

	}
//--------
	{
		const int VECTOR_SIZE = 8 ;

		// Define a template class vector of integers
		typedef vector<int > IntVector ;

		//Define an iterator for template class vector of integer
		typedef IntVector::iterator IntVectorIt ;

		IntVector Numbers(VECTOR_SIZE) ;   //vector containing numbers

		IntVectorIt start, end, it, last;

		start = Numbers.begin() ;   // location of first
									// element of Numbers

		end = Numbers.end() ;       // one past the location
									// last element of Numbers

		//Initialize vector Numbers
		Numbers[0] = 10 ;
		Numbers[1] = 20 ;
		Numbers[2] = 10 ;
		Numbers[3] = 15 ;
		Numbers[4] = 12 ;
		Numbers[5] = 7 ;
		Numbers[6] = 9 ;
		Numbers[7] = 10 ;


		cout << "Before calling remove" << endl ;

		// print content of Numbers
		cout << "Numbers { " ;
		//CDT debug到这就报错
		for(it = start; it != end; it++)
			cout << *it << " " ;
		cout << " }\n" << endl ;
		//remove函数要引入<algorithm>头文件,“需要被删除”的元素被移到了区间的尾部。它返回一个迭代器，指向第一个“需要被删除”的元素。
		//begin()只要<vector>头文件,其实就是vec.begin();
		// remove all elements from Numbers that match 10
		 last = remove(start, end, 10) ;

		cout << "After calling remove" << endl ;

		// print content of Numbers
		cout << "Numbers { " ;
		for(it = start; it != end; it++)
			cout << *it << " " ;
		cout << " }\n" << endl ;

		//print number of elements removed from Numbers
		cout << "Total number of elements removed from Numbers = "
			<< end - last << endl ;

		//print only the valid elements of Number
		cout << "有效的元素为of Numbers { " ;
		for(it = start; it != last; it++)
			cout << *it << " " ;
		cout << " }\n" << endl ;

		//后面的并没有删除元素，只是修改了元素
		for ( auto it=Numbers.begin() ; it != Numbers.end() ; it++ )
		{
			cout << " " << *it;
		}

		//----
		std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		print_container(c);

		c.erase(c.begin());
		print_container(c);

		c.erase(c.begin()+2, c.begin()+5);
		print_container(c);

		// Erase all even numbers (C++11 and later)
		for (std::vector<int>::iterator it = c.begin(); it != c.end(); ) {
		  if (*it % 2 == 0) {
			  it = c.erase(it);//遍历时删除 ，要重新赋值才行，返回iterator是跟随最后删除的元素
		  } else {
			  ++it;
		  }
		}
		print_container(c);

	}
      //----C++ 20


	auto l2=[](vector<int> & vec){
		//老的方式
		//remove函数要引入<algorithm>头文件,“需要被删除”的元素被移到了区间的尾部。它返回一个迭代器，指向第一个“需要被删除”的元素。
		//begin()只要<vector>头文件,其实就是vec.begin();
		auto old_end=end(vec);
		auto iter_end=std::remove(begin(vec),end(vec),5);
		//CDT debug到这就报错
		/*
		 cout << "remain Numbers { " ;
		for ( auto it=vec.begin() ; it != iter_end; it++ )
		{
			cout << " " << *it;
		}
		cout << "} \n invalid Numbers { " ;
		for ( auto it=iter_end ; it != vec.end(); it++ )//old_end 或 vec.end() 一样，即vec.end()的返回值没有变
		{
			cout << " " << *it;
		}
		 cout << "} \n all Numbers { " ;
		for ( auto it=vec.begin() ; it != vec.end(); it++ )
		{
			cout << " " << *it;
		}
		*/
		vec.erase(std::remove(begin(vec),end(vec),5),end(vec));//返回的iterator中也要删除，返回用
		cout << "} \n after erase all Numbers { " ;//调用了erase后还是一样？
		for ( auto it=vec.begin() ; it != vec.end(); it++ )
		{
			cout << " " << *it;
		}
		 cout << "} \n " ;


	};
	vector v{1,2,4,5,6};
	l2(v);
	//新的方式
	vector v2{1,2,4,5,6};
	std::erase(v2,5); //<algorithm>头文件
	cout<<"new___"<<endl;
	print_container(v2);





	return 0;
}
};
