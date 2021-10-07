#include <stack>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

namespace sort
{

	void quicksort(int a[],int l,int h)//low,high
	{
		if (l>=h)
			return ;
		int j ,i,key;
		i=l;j=h;key=a[i];
		while(i<j)//每个都有i<j的判断
		{
			while(i<j && a[j]>key)//从右边开始,找到一个比key小的(这里是第一个)
				j--;
			if (i<j)
				a[i++]=a[j];
			while (i<j && a[i]<key)//从左边开始,找到一个比key大的
				i++;
			if (i<j)
				a[j--]=a[i];
		}
		a[i]=key; //i指向==j指向时
		if (l<i-1)
			quicksort(a,l,i-1);
		if (i+1<h)
			quicksort(a,i+1,h);

	}

	void InsertSort(int array[], int length)//直接插入排序(倒序查找)
	{
		int i, j, key;
		for (i = 1; i < length; i++)
		{
			key = array[i];
			for (j = i - 1; j >= 0 && array[j] > key; j--)//找到比key小的元素 移到前面(j--),
			{
				array[j + 1] = array[j];//元素向后推,后面的等于前面的,直到key >=的,
			}
			array[j + 1] = key;
		}
	}




	int cmp(const void *a, const void *b)
	{
		return *(int *)a - *(int *)b;
	}
	void printResult(int array[],int n)
	{
		int i;
		for(i=0;i<n;i++)
			printf("%d ",array[i]);
	}
	int main(int argc,char **argv)
	{
		  int arr[9]={5, 3, 7, 4, 1, 9, 8, 6, 2};

		  //qsort(arr, 9, sizeof(int), cmp);//stdlib.h中的
		  //quicksort(arr,0,8);//OK
		  //InsertSort(arr,9);//OK


		  printResult(arr,9);
		  return 1;
	}

}


