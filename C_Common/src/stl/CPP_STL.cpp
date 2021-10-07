#include <fstream>
//#include <strstream>
#include <iostream>
#include <iomanip>

#include <stack>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <bitset>

#include <algorithm>
#include <typeinfo>
#include <string>
//CPP的头文件在要namespace外#include
namespace stl_cpp
{
	using namespace std;//在<string.h>前后，没关系
	//#include <string.h>//因用了using namespace,使用了C 函数strlen要在namespace 里,#include C文件
	int consoleIO()
	{
		int a;
		char * b=new char[20];
		cout<<"输入一个数 空格 字串:"<<endl;
		cin>>a>>b;//多个输入 以 空格 分隔
		if(!cin)
		{
			cerr<<"输入错误"<<endl;
			return -1;
		}
		cout<<b<<endl;
		delete b;
		cout<<"十进制:"<<dec<<a<<endl;
		cout<<"十六进制:"<<hex<<a<<endl;
		cout<<"八进制:"<<setbase(8)<<a<<endl;//另一种进制的方法

		float pi=3.1415926f;
		cout<<"3位包括小数点:"<<setprecision(3)<<pi<<endl;
		cout.precision(2);//同上面 <<setprecision(2)
		cout<<"2位包括小数点:"<<pi<<endl;

		cout<<"科学计算法:"<<setprecision(5)<<setiosflags(ios::scientific)<<pi<<endl;

		cout.unsetf(ios::oct);//同 resetiosflags(ios::dec)
		cout.setf(ios::dec);
		cout<<"小数计算法:"<<setiosflags(ios::fixed)<<pi<<resetiosflags(ios::dec)<<endl;//VC2012 以0x方式输出,设置dec,setbase(10)没用??


		char pt[]="Chain";
		cout<<setw(10)<<setfill('*')<<pt<<endl;//在左边填充*
		cout<<setw(10)<<pt<<setfill('*')<<endl;//也是在左边填充*
		cout<<setfill('*')<<setw(10)<<pt<<endl;//也是在左边填充*

		cout.put('a');
		cout.put(65+32);//a
		cout.put(71).put(79).put(79).put(68).put('\n');//C++
		putchar('A');//C


		int aa=29,bb=1001;
		cout<<endl<<aa<<setw(6)<<bb<<endl;//29**1001,setw是对后的影响

		cout<<"请输入任何字符-get1,以/结束"<<endl;
		char ch[20];
		cin.get(ch,10,'/');
		cout<<ch<<endl;

		cout<<"请输入任何字符-get2,以/结束"<<endl;
		cin.get(ch,10,'/');  //会使用上一次的输入的结束位置开始
		cout<<ch<<endl;

		cin.clear();//没用???

		//getline读终止字符后,指针向后移动一个,get则不移动

		cout<<"请输入任何字符-getline 4,以/结束"<<endl;
		cin.getline(ch,18,'/');   //会使用上一次的输入的结束位置开始
		cout<<ch<<endl;

		return 1;
	}
	int readWriteTextFile()
	{
		//------------写 文件文本
		ofstream outfile;
		outfile.open("d:/temp/f1.dat",ios::out|ios::binary|ios::trunc);//ios::trunc覆盖和建立,ios::app,
		if(!outfile)//失败返回0
		{
			cerr<<"文件打开失败"<<endl;
			return -1;
		}

		outfile<<"这是使用C++写的文件内容 \r\n 第二"<<endl;
		outfile<<"第三行"<<endl;
		outfile.put('Z');

		string cpp_data="write方法";//是C++语言的方式 string
		int len=cpp_data.length();
		const char * data =cpp_data.c_str();//带'\0'
		//const char* data =cpp_data.data();//不带'\0'

		//char* data ="write方法";
		//int len=strlen(data);//是C语言的方式,对于使用了using namespace,要在里面#include


		outfile.write(data,len);//可以是二进制数据,sizeof(struct1)

		outfile.close();

		//------------读文本 文件

		ifstream infile;
		infile.open("d:/temp/f1.dat",ios::in);

		char * str=new char[50];
		infile>>str; //以endl结束
		cout<<"从文件中读到的内容:"<<str<<endl;
		infile>>str;
		cout<<"2:"<<str<<endl;
		infile>>str;
		cout<<"3:"<<str<<endl;

		delete[] str;

		char x;
		infile.get(x);
		cout<<"rn:="<<x<<endl;
		infile.get(x);
		cout<<"z:="<<x<<endl;

		//len++;//为'\0'
		while(infile.get(x))//有单字节,有双字节
		{
			if(--len<0)
				break;
			cout<<"o:="<<x<<endl;
		}
		infile.close();

		return 1;
	}

	int readWriteBinaryFile()
	{
		//------------写 二进制文本
		ofstream outfile;
		outfile.open("d:/temp/f1.dat",ios::out|ios::binary|ios::trunc);//ios::trunc覆盖和建立,ios::app,
		if(!outfile)//失败返回0
		{
			cerr<<"文件打开失败"<<endl;
			return -1;
		}
		struct Student{//可无名
			int id;
			char name[10];
			char sex;
		}lisi[2]={{100,"李四",'T'},{101,"李四2",'F'}};
		outfile.write((char*)&lisi[0],sizeof(lisi[0]));
		outfile.write((char*)&lisi[1],sizeof(lisi[1]));
		outfile.close();

		//------------读二进制 文件

		ifstream infile;
		infile.open("d:/temp/f1.dat",ios::in);
		Student readData;

		infile.read((char*)&readData,sizeof(Student));
		cout<<readData.id<<":"<<readData.name<<":"<<readData.sex<<endl;
		infile.read((char*)&readData,sizeof(Student));
		cout<<readData.id<<":"<<readData.name<<":"<<readData.sex<<endl;

		int size=(sizeof(Student));
		infile.seekg(-size,ios::cur);//还有ios::beg,ios::end
		int current=infile.tellg();
		cout<<"current:"<<current<<endl;
		infile.read((char*)&readData,sizeof(Student));
		cout<<readData.id<<":"<<readData.name<<":"<<readData.sex<<endl;

		infile.close();


		return 1;
	}
	int STL_Container()
	{
		vector<int> the_vector; //是数组
		vector<int>::iterator the_iterator;
		for (int i=3; i < 9; i++)
			the_vector.push_back(i);//向尾部加
		the_iterator = the_vector.begin();
		cout << "first:" << *the_iterator << endl;
		for (the_iterator = the_vector.begin();the_iterator != the_vector.end();the_iterator++ )
		{
			cout <<*the_iterator << endl;
		}
		cout <<"数组 vector的size:"<<the_vector.size()<< endl;
		cout <<"数组 vector的max_size："<<the_vector.max_size()<< endl;

		cout <<"数组 vector的front："<<the_vector.front()<< endl;//取得第一个
		cout <<"vector的back："<<the_vector.back()<< endl;//取最后一个元素

		cout <<"vector的end-1："<<*(the_vector.end()-1)<< endl;//iterator到未尾

//		cout <<"vector的empty："<<the_vector.empty()<< endl;//是否为空
//		the_vector.clear();//清空

		vector<int> the_vector2;
		the_vector2.assign(the_vector.begin(),the_vector.end());//the_vector复制到the_vector2中
		cout <<"assign复制后的vector2[1]的值："<<the_vector2[1] << endl;

		the_vector2.assign(8,20);//修改vector长度为8,值全是20
		cout <<"assign修改后"<<the_vector2[0] << endl;//20
		cout <<"assign修改后"<<the_vector2[7] << endl;//20
		the_vector.insert(the_vector.begin()+2 ,33);
		cout <<"assign insert 33后"<<the_vector[2] << endl;

		cout <<"assign insertthe_vector2后"  << endl;
		the_vector.insert(the_vector.begin()+2,the_vector2.begin(),the_vector2.end());
		for (the_iterator = the_vector.begin();the_iterator != the_vector.end();the_iterator++ )
		{
			cout <<*the_iterator << endl;
		}
		//the_vector.pop_back();//从后删
		vector< vector<int> > Array(10);//第一维必须给初始大小,二维大小可不给,也可给


		//--------C++ list 和vector区别
		vector<int> v;
		list<int> l;
		for (int i=0; i<8; i++)     //往v和l中分别添加元素
		{
			v.push_back(i);
			l.push_back(i);
		}

		cout << "v[2] = " << v[2] << endl;
		//cout << "l[2] = " << l[2] << endl;       //编译错误,list没有重载[]
		cout << (v.begin() < v.end()) << endl;
		//cout << (l.begin() < l.end()) << endl;   //编译错误,list::iterator没有重载<或>
		cout << *(v.begin() + 1) << endl;

		vector<int>::iterator itv = v.begin();
		list<int>::iterator itl = l.begin();
		itv = itv + 2;
		//itl = itl + 2;                  //编译错误,list::iterator没有重载+
		itl++;itl++;   					 //list::iterator中重载了++，只能使用++进行迭代访问。
		cout << *itv << endl;
		cout << *itl << endl;


		//--------list vector 删除方法名不同
		cout <<"list size"<<l.size()<< endl;
		l.remove(2);
		cout <<"remove后list size"<<l.size()<< endl;

		v.erase(v.begin()+2);


		l.push_front(300);//list 双向的链表,只list可从表头加元素,vector没有这方法
		cout <<l.front()<<endl;
		l.pop_front();//从表头删除一个元素,再调用 front();

		//vector有at(i)来仿问元素,其实是基于数组实现

		//遍历与list同,使用iterator
		int myints[] = {75,23,65,42,13,75};
		list<int> mylist (myints,myints+6);//from,to
		list<int>::iterator it;
		cout << "list 双向的链表  不排序的,可有相同的";
		for ( it=mylist.begin() ; it != mylist.end(); it++ )
		cout << " " << *it;


		//---set
		set<int> myset;
		set<int>::iterator set_iter;
		set_iter=myset.begin();
		myset.insert (set_iter,25);
		myset.insert (set_iter,24);

		for (int i=1; i<=5; i++)
		  myset.insert(i);
		int mapints[]= {5,10,15};
		myset.insert (mapints,mapints+3);

		cout << "排序的没有重复元素的Set  " << *set_iter;
		for (set_iter=myset.begin(); set_iter!=myset.end(); set_iter++)
		 cout << " " << *set_iter;


		//---stack,
		stack<int> s;
		s.push(123);
		s.push(456);
		while(!s.empty())
		{
			cout <<"\n statck 顶:"<<s.top()<< endl;
			s.pop();//选top()再pop
		}

	  //-- map ,
	  map<char,int> mymap;
	  map<char,int>::iterator map_iter;
	  mymap['b'] = 100;
	  mymap['a'] = 200;
	  mymap['c'] = 300;

	  mymap.insert ( pair<char,int>('a',100) );//不带位置的,失败,而不是覆盖
	  mymap.insert ( pair<char,int>('z',200) );

	  map_iter = mymap.begin();//end()也是一样的,因是按key排序的
	  mymap.insert (map_iter, pair<char,int>('x',300));//带位置的
	  mymap.insert (map_iter, pair<char,int>('y',400));
	  cout<<"是排序的 map,有相同key失败   "<<endl;
	  for ( map_iter=mymap.begin() ; map_iter != mymap.end(); map_iter++ )
		cout << (*map_iter).first << " => " << (*map_iter).second << endl;//first是key,second是value,默认按key排序的

	  cout <<"使用[]仿问"<<mymap['b']<<endl;
	  cout <<"使用find仿问"<< mymap.find('b')->second<<endl;

	  //--multimap
	  multimap<char,int> mymultimap;
	  multimap<char,int>::iterator multimap_iter;
	  mymultimap.insert (pair<char,int>('b',20));
	  mymultimap.insert (pair<char,int>('a',10));
	  mymultimap.insert (pair<char,int>('b',150));
	  cout<<"可以有相同的key,也是排序的 multimap   "<<endl;
	  for ( multimap_iter=mymultimap.begin() ; multimap_iter != mymultimap.end(); multimap_iter++ )
		  cout << (*multimap_iter).first << " => " << (*multimap_iter).second << endl;

	 //--C++11中新加 unordered_map,unordered_multimap,unordered_set,unordered_multiset,,,,,forward_list,,array
	//  http://www.cplusplus.com/reference/stl/unordered_map/


	//---queue,队列,FIFO (first in ,first out)
	//---deque 双向的

	//--bitset
	  bitset<10> bac (120ul);          // 10是长度,unsigned long

	  bitset<4> first (string("1001"));
	  bitset<4> second (string("0011"));
	 cout << (first^=second) << endl;          // 1010 (XOR,assign)
	 cout << (first&=second) << endl;          // 0010 (AND,assign)
	 cout << (first|=second) << endl;
	 //其它的按位操作<<=,>>=,<<,>>,==,!=,^,&,|,~


	   bitset<5> mybits (string("01011"));
	   cout << mybits <<endl; //把0,1以true,flase显示

	   cout << "bitset 有1吗" << mybits.any() << endl;
	   cout << "bitset 没有1吗" << mybits.none() << endl;
	   cout << "bitset 含有1的个数" << mybits.count() << endl;
	   cout << "bitset 总数" <<  mybits.size()  <<endl;

	   cout << "bitset []索引从右边开始?" <<  mybits[0]  <<endl;
	   cout << "bitset test 索引从右边开始?:" <<  mybits.test(0)  <<endl;
	   mybits[0]=1;
	   cout<<mybits<<endl;
	   cout << "bitset []" <<  mybits[0]  <<endl;

	   cout << "bitset set:" << mybits.set(0,0) << endl;//返回修改的,第几个,是几,索引,0开始
	   cout << "bitset test:" <<  mybits.test(0)  <<endl;//读


	   bitset<5> bits (string("01011"));
	   cout << "bits 的索引从右边开始?:\n";
	   for (size_t i=0; i<bits.size(); ++i)
	     cout << bits.test(i) << endl;//

	   bool s123=true;//有bool ,true ,false

	    cout << bits.flip(2) << endl;//只对索引为2的位取反  	,索引从右边开始??  01111
	    cout << bits.flip() << endl;//同~操作符      			,索引从右边开始??  10000

	  return 1;
	}



	struct myclass
	{
		bool operator() (int i,int j)
		{
			return (i<j);
		}
	} myobject;
	bool myfunction (int i,int j)
	{
		return (i<j);
	}
	bool compare_as_ints (double i,double j)
	{
		return (int(i)<int(j));
	}
	int STL_Algorithm()
	{
		int myints[] = {32,71,12,45,26,80,53,33};
		  vector<int> myvector (myints, myints+8);
		  vector<int>::iterator it;
		  // using default comparison (operator <):
		  sort (myvector.begin(), myvector.begin()+4);           //(12 32 45 71)26 80 53 33

		  // using function as comp
		  sort (myvector.begin()+4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)

		  // using object as comp
		  sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

		  // print out content:
		  cout << "myvector contains:";
		  for (it=myvector.begin(); it!=myvector.end(); ++it)
		    cout << " " << *it;



		  //----stable_sort 会保留相等元素的位序
		  cout <<"stable_sort 会保留相等元素的位序"<< endl;

		    double mydoubles[] = {3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58};

		    vector<double> myvector_2;
		    vector<double>::iterator it_2;

		    myvector_2.assign(mydoubles,mydoubles+8);//不修改原集合的内容来排序

		    cout << "using default comparison:";
		    stable_sort (myvector_2.begin(), myvector_2.end());
		    for (it_2=myvector_2.begin(); it_2!=myvector_2.end(); ++it_2)
		      cout << " " << *it_2;

		    myvector_2.assign(mydoubles,mydoubles+8);

		    cout << "\nusing 'compare_as_ints' :";
		    stable_sort (myvector_2.begin(), myvector_2.end(), compare_as_ints);
		    for (it_2=myvector_2.begin(); it_2!=myvector_2.end(); ++it_2)
		      cout << " " << *it_2;

		   return 1;
	}
	int STL_string()
	{
		//---- http://www.cplusplus.com/reference/string/string/

		string str2 = "二三四";
		str2+="OK";			//可用+=
		cout<<"str2:"<<str2<<endl;

		string res=str2 + "456"; //可用+
		cout<<"相加:"<<res<<endl;

		if("abc">"123")//还有>=,<,<=,!=,==
			cout<<"大于的"<<endl;
		else
			cout<<"小于的"<<endl;

		int comp=res.compare("123");//类似 >=,<,<=,!=,==

		res.append("test");//类似+=
		res.push_back('!');//只在尾加

		cout<<"append相加:"<<res<<endl;





		char * s="abc 123";
		string str(s);		//可用char* 构造初始化
		cout<<"str:"<<str<<endl;

		str.assign(10,'*');//会替代以前的内容
		cout << str << endl;

		str.assign("pangrams are cool",7);
		cout << str << endl;

		//length()和size()是一样的
		cout<<"length/size:"<<str.length()<<endl; //assign后的长度是最初的长度,即abc 123的长度7,

		str.insert(3," not right",4);//插入,会报out_of_range,
		cout<<"插入:"<<str<<endl;

		str.insert (str.end(),3,'.');//end()返回iterator

		str.erase(str.begin()+10,str.end());
		cout<<"删除:"<<str<<endl;

		cout<<"length/size:"<<str.length()<<endl;
		str.replace(4,6," is good ");
		cout<<"替换:"<<str<<endl;

		const char * p_char = str.c_str();//自动加'\0',,不能修改返回的数据
		const char * p_char2 = str.data();//不加'\0',不能修改返回的数据


		char buffer[20];
		size_t length=str.copy(buffer,6,5);
		buffer[length]='\0';		//copy要手式加'\0'
		cout<<"复制的:"<<buffer<<endl;

		char array[50]="1234567中国";
		string array_str(array);

		string sub=array_str.substr(3,4);
		cout<<"substr:"<<array_str.substr(3,4)<<endl;//从第三个开始,长度为4

		sub.swap(array_str);//交换
		cout<<"swap结果:"<<array_str<<":"<<sub <<endl;

		string artical="this is a test for C++		,ok next subject";
		int len=artical.length();
		for(int i=0;i<len;i++)
		{
			cout<<artical.at(i)<<endl;//界时会抛出out_of_range异常,不能仿问'\0'
			//cout<<"[2]:"<<s[2]<<endl;//可用[]
		}
		int found=artical.find("test");
		cout<<"find test位置:"<<found<<endl;
		found=artical.find('e');
		cout<<"find e位置:"<<found<<endl;

		found=artical.rfind('t',20);//从20开始从后向前查找字符c在当前串中的位置
		cout<<"返向找到位置:"<<found<<endl;

		found=artical.find_first_of('t',4);//从4开始查找字符t第一次出现的位置
		cout<<"find_first_of到位置:"<<found<<endl;

		found = artical.find_first_not_of("abcdefghijklmnopqrstuvwxyz ",0);
		cout<<"find_first_not_of 到位置:"<<found<<endl;//即+的位置

		found = artical.find_last_not_of("abcdefghijklmnopqrstuvwxyz ",-1);//-1 string::npos全部字串,这个字串是从后向前读, -3
		if(string::npos!=found)	//如找不到返回string::npos
			cout<<"find_last_not_of 到位置:"<<found<<endl;//即,的位置

//		artical.clear();//清空
//		cout<<"是否为空:"<<artical.empty()<<endl;

//		string input;
//		getline (cin,input);//从cin文件中读一行到input


		return 1;
	}
	int main(int argc,char* argv[] )
	{
		return consoleIO();
		//return readWriteTextFile();
		//return readWriteBinaryFile();
		//return STL_Container();
		//return STL_string();
		//return STL_Algorithm();

	}

}


