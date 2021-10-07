#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace exercise
{
	void countword()
	{
		string artical="this is a test for C++		,ok next subject";

		vector<string> all;
		const char * str=artical.c_str();
		int len=strlen(str);
		char dest[len+1];
		int count=0;
		strcpy(dest,str);
		char* pch = strtok (dest," \t\r\n");
		while (pch != NULL)
		{
			cout<<pch<<endl;
			count++;
			all.push_back(string(pch));
			pch = strtok (NULL," \t\r\n");
		}

		vector<string>::iterator iter = all.begin();
		for(;iter!=all.end();iter++)
			cout<<*iter<<"--";
		cout<<"\ncount:"<<count<<endl;

	}

	class base
	{
	};
	void show(base*pb,void(base::*pf)())
	{
		(pb->*pf)();//写法
	}



	int main(int argc,char **argv)
	{
		//countword();



		double pi=3.14;
		cout<<setprecision(1)<<pi<<endl;//  包括小数点
		struct P {
				char data[8];
				//P *  next;//4
				P *  previous;//是指针就是占4个字节长,4x8=32位,因是32位CPU
			};
		short * point;
		P * abc;

		int size=sizeof (point);
		size=sizeof(short);
		size=sizeof (P);
		size=sizeof (abc);
		cout<<size;
	}

}
