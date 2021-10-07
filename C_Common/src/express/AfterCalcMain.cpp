/*
1.后缀式 求值
  如表达式 a*b + (c-d/e) * f
  的后缀式为 ab*   cde/-f*  +   ,特点,操作数顺序不变

  找后缀式,所找到操作数放入栈 直到有操作符,用这个操作符,把栈顶两个元素取出算,把结果再加入栈顶,依次...


 2.如何把表达式转换成后缀式,
  因操作数顺序不变,第一个运算符出现不确定是否要算,第二个运算符出现和第一个运算符比较优先级,如第二个比第一个小,则把第一个放入结果栈(后缀式栈),第二个放入中间栈,
	如第二个比第一个大,还不确定,要和第三个比较,
	如果* / 优先级相等,先把中间栈顶的* / 取出放入结果栈,再把自己* / 放入中间栈
	+ - 低优先级,入结果栈时要先看是否中间中是否有 (

  1)存后缀式的结果栈,  保存从栈底到栈顶的后缀式
  2)存操作符比较的中间栈,如果新来的运算符比栈里的高,入本栈,如比栈里低,则出栈到后缀式栈的顶部,自己入栈,可用空格来区分多个数
	//为了第一个运行符的比较,先在栈底加入'#"符号,优先级最低,
	如'(' 直接放入,中间如多个运算符的比较和前相同 ,直到')',把中间栈的到括号内的所有运算符 放入 结果栈
*/


/*
void transform(char suffix[],char exp[]);//转换表达式到后缀式
{
	InitStack(S);
	Push(S,'#');
	p=exp;
	ch=*p;
	while(!StackEmpty(S))
	{
			if(!IN(ch,OP))
				Pass(Suffix,ch);
			else
				switch(ch)
				{
				case '(' :Push(S,ch);break;
				case ')':
					{
						Pop(S,c);
						while(c!='(')
						{
							Pass(Suffix,c);
							Pop(S,c);
						}
						break;

					}
				default :
					{
						while(!Gettop(S,c) && (precede(c,ch)))
						{
							Pass(Suffix,c);
							Pop(S,c);
						}
					}
				}
			if(ch!='#')
			{
				p++;
				ch=*p;
			}
			break;
	}

}
*/

//  5+16*(4/2+4)*2#
//  (3+4)*2#

#include <iostream>
#include <string>
#include <stdlib.h>

namespace express
{

using namespace std;

char ex[100];//存储后缀表达式
char str[100];//存储算术表达式
char stack[100];//作为栈使用
char ch;//当前判断的字符
int i=0;//i为算术表达式str的下标
int t;//t为后缀式ex的下标
int top=0;//top为栈顶
void trans();//转换函数
void compute();//计算后缀式的值

void trans()//将中缀式转换为后缀式
{
cout<<"输入一个算术表达式，以#号结束："<<endl;
while(str[i]!='#')//中缀式以#号结束
{
   i++;//因为i的初值设为0
   cin>>str[i];
}


//开始扫描
t=1;
i=1;
ch=str[i];
i++;//i指向当前扫描字符的下一位
while(ch!='#')//逐个扫描，直至遇到#号结束
{
   switch(ch)
   {
   case'('://遇到（，进栈
    top++;
    stack[top]=ch;
    break;
   case')'://遇到），将靠近栈顶的第一个左括号上面的运算符全部依次弹出，送至后缀式队列后，再丢弃左括号。
    while(stack[top]!='(')
    {
     ex[t]=stack[top];
     top--;
     t++;
    }
    top--;//丢弃（
    break;
   case'+':
   case'-':
    while(top!=0 && stack[top]!='(')
    {
     ex[t]=stack[top];
     top--;
     t++;
    }
    top++;//因为top的初值为0
    stack[top]=ch;
    break;
   case'*':
   case'/':
    while(stack[top]=='*'|| stack[top]=='/')
   {
    ex[t]=stack[top];
    top--;
    t++;
   }
   top++;
   stack[top]=ch;
   break;
 
   /*注意！除操作数外，其它符号都要用到栈*/
   default:while(ch>='0' && ch<='9')//遇到操作数直接送至后缀式队列
     {
      ex[t]=ch;
      t++;
      ch=str[i];
      i++;//此时i指向操作数之后的运算符的后一位！！
     }
    i--;//要在操作数之后，运算符之前添加空格符
    ex[t]=' ';//用空格符隔开
    t++;

   }//switch结束

   ch=str[i];//仿照default中的，返回添加空格符之前的操作
   i++;
}//结束while


while(top!=0)//仍有运算符在栈中
{
   ex[t]=stack[top];
   t++;
   top--;
}
ex[t]=' ';//不能省，若省掉则无法进入compute函数??

for(int j=1;j<i-1;j++)
   cout<<str[j];
cout<<"的后缀式为：";
for(int j=1;j<t;j++)
cout<<ex[j];

}

void compute()
{
float stack[100];//作为栈使用
int d;//用于存放当前的计算结果
char ch;
int t=1;
int top =0;
ch=ex[t];
t++;

while(ch!=' ')//此空格符为后缀式中的最后一个字符，与上文中的" ex[t]=' '; "相对应
{
   switch(ch)
   {
   case'+':
    stack[top-1]=stack[top-1]+stack[top];
    top--;
    break;
   case'-':
    stack[top-1]=stack[top-1]-stack[top];
    top--;
    break;
   case'*':
    stack[top-1]=stack[top-1]*stack[top];
    top--;
    break;
   case'/':
    if(stack[top]!=0)
     stack[top-1]=stack[top-1]/stack[top];
    else
    {
     cout<<"\n除零错误!"<<endl;
     exit(0);//异常退出
    }
    top--;//两个操作数算出一个结果存放到栈顶，那两操作数便可丢弃，故top-1
    break;
   default:
    d=0;
    while(ch>='0' && ch<='9')
    {
     d=10*d+ch-'0';//将数字字符转化为对应的数值，*10是与大于10的数值时要进位
     ch=ex[t];
     t++;
    }
    top++;
    stack[top]=d;//栈顶存放当前计算结果
 
   }//switch结束
   ch=ex[t];//跳过空格符，扫描下一个运算符或操作数
   t++;
}
cout<<"\n计算结果为:"<<stack[top]<<endl;
int x;
cin>>x;
}




int main(int argc, char* argv[])
{
	trans();
	compute();
	return 1;
}

}
