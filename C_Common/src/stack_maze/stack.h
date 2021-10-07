#ifndef _STACK_H
#define _STACK_H

#include "data.h"

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 10
typedef struct
{
	ElemType * base;
	ElemType * top;
	int size;
}STACK;
STACK * InitStack();

int Push(STACK *s,ElemType *e);
int Pop(STACK *s ,ElemType *e);
int IsEmpty(STACK *s);
void DestroyStack(STACK *s);


#endif