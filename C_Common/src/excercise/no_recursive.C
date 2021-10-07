#include <stack>
#include <vector>
#include <iostream>
using namespace std;
namespace  no_recursive
 {
	#include <stdio.h>

	long rabit(long n) //使用递归
 	{
 		//java.lang.StackOverflowError
 		if (n<2)
 			return 1;
 		else
 		{
 			int abc=1836311903;
 			/*
 			int i=1234567890l;
 			    //1836311903 //45
 			int  a=1234567890 + 1234567890;//负数溢出
 			long  b=1234567890l + 1234567890l;//加l
 			*/
 			long a=rabit(n-1);
 			long b=rabit(n-2);
 			long s=a+b;
 			return s;
 		}
 	}

 	 //潭浩强  Fibonacci 数学问题 兔子 三个月生
 	//如果一对兔子每月能生一对小兔（一雄一雌），而每对小兔在它出生后的第三个月里，又能开始生一对小兔
 	long rabit1(long n)// n=11;//月数
 	{
 		long  f1=1,f2=1;
 		for(int i=1;i<=n/2;i++)  // 除2是因加了两次
 		{
 			printf("%12d  %12d\n",f1,f2);
 			f1=f1+f2;
 			f2=f2+f1;
 		}
 		return f1;


 	}
	 int rabit2(int n)//后一个数等于前两个数相加
	 {
		 if(n==0)
			 return 0;
		 int x=0,y=1;
		 for(int i=2;i<=n;i++)
		 {
			 int z;
			 z=y;
			 y=x+y;
			 x=z;
		 }
		 return y;
	 }
	 int qsort_no_recursive(vector<int> &data_list)
	 {

	 }



	#define MAX_SIZE      10
	typedef int elem;
	void swap(elem& a, elem& b)
	{
		if (&a != &b)
		{
			a ^= b;
			b ^= a;
			a ^= b;
		}
	}
	int partition(elem *pData, int low, int high)
	{
		elem key = pData[low];
		while (low < high)
		{
			while (low < high && pData[high] >= key)
				high--;
			swap(pData[low], pData[high]);
			while (low < high && pData[low] <= key)
				low++;
			swap(pData[low], pData[high]);
		}
		return low;
	}

	//这个是原始的算法

	void qsort(elem* pData, int low, int high)
	{
		if (low < high)
		{
			int pivot = partition(pData, low, high);
			qsort(pData, low, pivot - 1);
			qsort(pData, pivot + 1, high);
		}
	}

	//这个是第一次转化成递归以后的算法
	void qsort2(elem* pData, int low, int high)
	{
		stack<int> st;
		if (low < high)
		{
			int pivot = partition(pData, low, high);
			st.push(low);
			st.push(pivot - 1);
			st.push(pivot + 1);
			st.push(high);
			while (!st.empty())
			{
				high = st.top();
				st.pop();
				low = st.top();
				st.pop();
				pivot = partition(pData, low, high);
				if (low < high)
				{
					st.push(low);
					st.push(pivot - 1);
					st.push(pivot + 1);
					st.push(high);
				}
			}
		}
	}

	//这个是转化成递归以后改进的算法
	void qsort3(elem* pData, int low, int high)
	{
		stack<int>  st;
		int tmp;
		if (low < high)
		{
			int pivot = partition(pData, low, high);
			st.push(low);
			st.push(pivot - 1);
			st.push(pivot + 1);
			st.push(high);
			while (!st.empty())
			{
				high = st.top();
				st.pop();
				low = st.top();
				st.pop();
				if (low < high)
				{
					pivot = partition(pData, low, high);
					tmp = pivot - 1;
					if (low < tmp)
					{
						st.push(low);
						st.push(tmp);
					}
					tmp = pivot + 1;
					if (tmp < high)
					{
						st.push(tmp);
						st.push(high);
					}
				}
			}
		}
	}

 	 int main(int argc,char **argv)
 	{
 		long count=rabit(42);//41=267914296,,42=433494437,如传42的话非常的慢,如更大就更不用说了
 		printf("使用递归:%l\n",count);
// 		 int res1=rabit1(10);
// 		 int res2=rabit2(10);
//
// 		printf("res1=%12d,res2= %12d\n",res1,res2);




 		elem data[MAX_SIZE] = { 12, 1, 13, 14, 67, 23, 12, 3, 90, 76 };
 		//qsort(data, 0, MAX_SIZE - 1);
 		qsort2(data, 0, MAX_SIZE - 1);
 		//qsort3(data, 0, MAX_SIZE - 1);
 		for (int i = 0; i < MAX_SIZE; i++)
 		{
 			cout << data[i] << " ";
 		}
 		cout << endl;
 		cin.get();

 		return 0;
 	}
 }



