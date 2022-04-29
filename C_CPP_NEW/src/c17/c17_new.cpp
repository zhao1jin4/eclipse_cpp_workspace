#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <shared_mutex>
#include <mutex>

using namespace std;

namespace c17_new
{
	namespace nestnamespace{//嵌入多层的namespace
		namespace xx{

		}
	}
	namespace nestnamespace::yy{//写法2

	}

	void printVector(const string & msg,const vector<string> &vec){
		cout<<msg<<",";
		for(const auto & i:vec){
			cout<<i<<" ";
		}
		cout<<endl;
	}
	template <typename T>
	auto printTypeValue(T const& value){
		if constexpr (is_integral<T>::value) //编译时,当条件不符合的，会被丢掉，就不会报错
		//if(is_integral<T>::value)//运行时,编译时并不知道value是什么类型
		{
			cout<<"T is int "<<value<<endl;
		}else
		{
			//编译时,知道是string.length()，而不是int.length(),用constexpr不报错
			cout<<"T is not int "<<value.length()<<endl;
		}
	}


	void myfunction () throw () {//c++17 不能在throw()里面加int等
	  throw  0.32;
	}
	int main(int argc, char* argv[])
	{
		vector<string> names={"wang","li","zhang","sun"};
		{//作用域
			const auto it=find(begin(names),end(names),"wang");
			if(it != end(names)){
				*it="***";//候改它
			}
			printVector("after wang",names);
		}
		{
			const auto it=find(begin(names),end(names),"li");//可以继续叫it
			if(it != end(names)){
				*it="**";
			}
			printVector("after li",names);
		}
		//if()中使用;号多隔多条语句，使用最后一个做结果,效果同上,switch( ; )也可以这做用
		if(const auto it=find(begin(names),end(names),"zhang");it != end(names)){
			*it="****";
		}
		printVector("after zhang",names);

		if(const auto it=find(begin(names),end(names),"sun");it != end(names)){//也可以继续用变量it
			*it="***";
		}
		printVector("after sun",names);


		for(int i=0;i<10;i++){

		}
		for(int i=0;i<10;i++){ //可以继续用变量i

		}


		if constexpr (1==2){ //编译时

		}

		printTypeValue(20);
		printTypeValue("this is string"s);

		map<string,int> mymap;//<map>
		mymap.insert ({"chinese",100} );
		auto mypair= mymap.insert ({"chinese",90} );
		if(mypair.second)//如已经存在就失败，和java的存在覆盖是不一样的
		{
			cout<<"put success"<<endl;
		}else
		{
			cout<<"put fail"<<endl;
			auto iter=mypair.first;//已存在的元素是什么
			//老的遍历方式
			for (auto  map_iter=mymap.begin() ; map_iter != mymap.end(); map_iter++ )
			{
				cout << (*map_iter).first << " => " << (*map_iter).second << endl;//first是key,second是value,默认按key排序的
			}

		}
		auto [position,success]= mymap.insert ({"chinese",80} ); //命名更加清晰
		//新的遍历方式
		for(const auto & [lang,score] : mymap)//命名更清晰
		{
			cout<<"lang="<<lang<<",score="<<score<<endl;
		}

//--------

		 shared_mutex my_share_mutex;
		 scoped_lock my_scope_lock;//  <mutex>头文件
		return 1;
	}

};


