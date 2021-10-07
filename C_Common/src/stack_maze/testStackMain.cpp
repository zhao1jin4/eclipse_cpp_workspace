#include "stack.h"
#include <stdio.h>


int main_statck(int argc, char* argv[])
{
	int num=1378,temp;
	STACK *s = InitStack();
	while(num)
	{
		temp=num%8;
		Push(s,(ElemType *)&temp);
		num/=8;
	}
	printf("result is:");
	while(!IsEmpty(s))
	{
		Pop(s,(ElemType *)&temp);
		printf("%d",temp);
	}

	DestroyStack(s);

	return 1;
}
