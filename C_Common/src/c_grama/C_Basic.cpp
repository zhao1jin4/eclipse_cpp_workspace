#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <climits>

namespace c_basic
{

#define M(a,b)(a)>(b)?(a):(b)  //不推荐用#define

int sum(int k)
{
	static int x=0;//static  用法
	return (x+=k);
}


//template<typename T>
//template<class T>
template<class T> T max(T a,T b,T c)//写法
{
	T x;
	if(a>b)
		x=a;
	else
		x=b;
	if(x<c)
		x=c;
	return x;
}



int min(int a,int b)
{
	return a<b?a:b;
}
void* returnFunc(){
  return (void*)min;
}
int (*returnFuncInPointer(int a))(int,int)//返回指向函数的指针,不易读
{
	 int (*p) (int ,int);//定义指向函数的针;
	 p=min;
	 return p;
}
//或者用,linux 信号处理函数signal就是这样的形式
typedef int (*FuncInPointer) (int ,int);
FuncInPointer  returnFuncInPointer2(int a)
{
	return returnFuncInPointer(22);
}


int (*returnArrayInPointer(int a))[2] //函数的返回值 是指向 int[2] 的指针;
{
	int (*data)[2];//是指针,指向 int[2] 的指针;
	data = (int(*)[2])malloc(2*sizeof(int));//这里是的强转写法(int(*)[2]),无名指针
	(*data)[0] = 1;
	(*data)[1] = 2;
	free(data);//这里为了测试,返回的值不能使用
	return data;
}
//或者用
typedef int(*ArrayInPointer)[2] ;
ArrayInPointer returnArrayInPointer2(int a)//这样可以的
{
	return returnArrayInPointer(1);
}

void pointerConstTest()
{
//------------const
	int temp=3;
	int other=33;

	//const放*前
	const int *A; // 或  int const *A; //const修饰指向的对象，A可变，A指向的对象不可变
	A=&temp; //OK
	//*A=4;//错误!!!, 不可修改指向的值


	//const放*后
	int * const B=&temp; 	//const修饰指针B，     B不可变，B指向的对象可变,必须给初值
	*B=4;//OK
	//B=&other;//错误!!!, 不可再指向其它
	const int *const C=&temp; 	//指针C和C指向的对象都不可变 , 必须给初值

//------------pointer

	int * array[5];//是数组,里存放int* 类型的指针
	int age=20;
	array[0]=&age;

	int chars[5]={0,1,2};
	int (*pointer)[5];//是指针,指向int[5]的数组
	pointer = &chars;
	printf("%d\n",(*pointer)[2]);//2
	//--
	  typedef int (*FUNC)(int, int);
	  FUNC func1 = min;
	  printf("%d\n",  func1(11,22));
	  printf("%d\n",  (*func1)(11,22));

	  FUNC func2 = &min;
	  printf("%d\n",  (*func2)(10,20));
	  printf("%d\n",  func2(10,20));

	  int(*minPtr2)(int,int)=&min;
	  int(**minPtr3)(int,int)=&minPtr2;//"指向函数指针" 的 指针
	  printf("%d\n",  (**minPtr3)(22,33));

	  FUNC func3 = NULL;
	  void* funcVoid=(void*)min;
	 // *(void **) (&func3) =funcVoid;//=前面是void*类型
	  *((void **) (&func3)) =funcVoid;//就是func3取地址，再强制为void ** 类型，再取值，再赋值(即先强转再赋值)
	  printf("%d\n",  (*func3)(10,20));
	  printf("%d\n",  func3(10,20));
	  //--

	void* func=returnFunc();
    int (*pMin)(int,int);
    pMin=(int (*)(int,int))func;//void* 强制转换为指向函数的指针
    printf("%d\n", pMin(22,33));

	//--
	FuncInPointer arrayCom[5];//是数组,里存放指针向函数的指针
	arrayCom[0]=min;
	int res=arrayCom[0](7,8);
	//方法2
	int (* arrayCom2[5]) (int,int);//是数组,里存放指针向函数的指针
	arrayCom2[0]=min;
	res=arrayCom2[0](7,8);

	 returnFuncInPointer2(22);
	 returnArrayInPointer2(22);

	printf("---------");

}

void basic()
{

	printf("%d\n",10*M(10,15));//10*(10)>(15)?(10):(15));

	int sum(int k); //static
	int total,i;
	for(i=1;i<=3;i++)
		total=sum(i);
	printf("---------s=%d\n",total);


	printf("a-A:%d\n",'a'-'A');//''可以做加减


	char sss[]="abc";
	char sss1[]={"abc"};//初始化

	int a[2][3]={{1,2,3},{4,5,6}};//初始化方式
	printf("请输入一个数:");

	//fflush(stdout);

	scanf("%d",&a[0][0]);//必须有 &

	char* str="20";
	int num=0;
	sscanf(str,"%d",&num);//可做类型转换

	printf("\n%x\n",194+9);//%x以16进制输出

	printf("----------\n");
	int x[3][6]={{1,2,3},{4,5,6},{7,8,9}},(*p)[6]=x,s=0,k;//   (*p)[6]
	for (k=0;k<6;k++)
		s=s+*(*(p+1)+k);
	printf("%d\n",s);


	int x12=(*(x+1))[2];//6
	int x01=*(*x+1)+2;//值为a[0][1]+2=4,注意错的
	int x12_error1=*(x+1)[2];//错的


	int x1,y1,z1;
	x1=(y1=1,z1=2);//逗号
	printf("%d\n",x1);//x1=2


	//	按运算符优先级从高到低：
	//	单目运算符->双目运算符->三目运算符->赋值运算符->逗号运算符
	//
	//	特别在双目运算符中,按 运算符优先级从高到低:算术运算符->移位运算符->关系运算符（其中== 和 !=优先级又较低）->逻辑运算符（按位与-〉按位异或 -〉按位或-〉逻辑与-〉逻辑或）！
	int xx=4;
	printf("xx=%d\n",xx+=xx*=(xx+1));//结果是40


	//int a=0;
	//(-a)++; //不可表达式 ++

	float abc=101.3;
	printf("%e\n",abc);//科学计数法
	printf("%d\n",!2);//0
	printf("%d\n",~2);//按位取反,-3


	float ff=123.0f;
	printf("result is:%20.3f\n",ff);

	float flo=10.0;
	printf("%8.2f\n",flo/2);

	int ox=012;//八进制
	printf("ox:%d\n",ox);


	printf("sizeof:%d\n",sizeof(unsigned short int  ));//2
	printf("sizeof:%d\n",sizeof(unsigned short ));//2 一样的

}
void complex()
{
	struct person
		{
			char name[10];
		}group[3]={{"abc"},{"def"},{"ghi"}};
		struct person * p_list=group;
		printf("%c%c%c\n",	(*(p_list+1)).name[0],//g
							(*(p_list++)).name[1],//b ,这里的++只影响前面的,不影响后面的
							(*(p_list+1)).name[2]);//f
		//结果是gbf  , C 语言的函数调用是从右向左压入栈
		//最后一个参数计算值 放入函数栈,第二个参数指针的改变不会影响最后一个参数的值


		union P //共用体,最长的
		{
			int grade;
			char posistion[10];
		};
		P p1;
		p1.grade=10;
		union P p2; //使用时最前的union可有可无
		p2.grade=20;

		printf("union的长度是:%d\n",sizeof(P));

		//---无名union联合体
		struct teacher{
			char name[20];
			union{ //这和用一个字段没什么区别？？
				float salary;
				float score;
			};
		};
		teacher li ={"lisi",20.3};
		teacher wang ={"wang",30.3};
		printf("li salary :%f\n",li.salary);
		printf("li score :%f\n",li.score);
		printf("wang salary :%f\n",wang.salary);
		printf("wang score :%f\n",wang.score);
		//--

		// mutable ???
}

enum Fruit {apple=1, pear=2, orange, banana};
void enumFunc(Fruit frt1)
{

	//frt1=Fruit.orange;//错误
	frt1=orange;

	enum Fruit frt2;//C使用
	Fruit frt3;//C++使用
	frt2=(Fruit)2;
	if(frt2==pear)
	{
		printf("pear\n");
	}
}
//int main(int argc,char* argv[] )
int main(int argc,char **argv)
{
	printf("argc:%d\n",argc);
	printf("argv:%s\n",*argv);//argv[0] is program name
	//printf("argv:%s\n",*(argv+1));
	//printf("argv:%s\n",*(argv+2));


	basic();
	complex();
	pointerConstTest();

	enumFunc(pear);//enum 不能 做|操作

	 int min=INT_MIN;//#include <climits>
	 int max=INT_MAX;
	return 1;
}



struct Student{
	int id;
	char name [20];
};
Student getStudent(int id)//方法可以返回结构体
{
	Student stu;
	return stu;
}


}







