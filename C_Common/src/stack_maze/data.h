#ifndef DATA_H
#define DATA_H

//typedef int ElemType;//for stack test



//for maze
typedef struct 
{
	int y;
	int x;
}POS;


typedef struct
{
	int sno;
	POS seat;
	int di;
}ElemType;

#endif