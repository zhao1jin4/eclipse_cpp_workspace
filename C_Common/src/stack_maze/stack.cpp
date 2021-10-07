#include "stack.h"
#include <stdlib.h>
#include <stdio.h>


STACK * InitStack()
{

	STACK * s=(STACK*)malloc(sizeof(STACK));
	if(s == NULL)
		exit(0);
	s->base=(ElemType*) malloc(STACK_INIT_SIZE * sizeof(ElemType));
	//int a;//一定要.cpp才不报错,还清理,C要求变量要在开始处定义

	if(s->base==NULL) 
		exit(0);
	s->top=s->base;
	s->size=STACK_INIT_SIZE;
	return s;

}

int Push(STACK *s,ElemType *e)
{
	if(s==NULL || e==NULL)
	{
		return 0;
	}
	if(s->top - s->base >= s->size)
	{
		s->base=(ElemType * ) realloc(s->base,(s->size+STACK_INCREMENT)*sizeof(ElemType));
		if(s->base==NULL)
			return 0;
		s->top = s->base + s->size;
		s->size =s->size+ STACK_INCREMENT;
	}
	
	*s->top++ = *e;
	return 1;

}

int Pop(STACK *s ,ElemType *e)
{
	if(s==NULL || e==NULL)
		return 0;

	if(s->base == s->top)
			return 0;
	*e = * --s ->top;//优先级 
	return 1;

}


int IsEmpty(STACK *s)

{
	return s->top == s->base ? 1 : 0;
}


void DestroyStack(STACK *s)
{
	free(s->base);
	free(s);
}



