

//迷宫
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//1 表示墙
int item[10][10]=
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,1,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

static const POS inPos={1,2},outPos={8,8};

int IsPass(POS curP)
{
	return item[curP.y][curP.x] == 0 ? 1 : 0;
}

POS NextPos(POS curP,int di)
{
	POS p=curP;
	switch(di)
	{
	case 0:		//enum 
		p.x--; //向 left 逆时针,这个x表示坐标,不是下标
		break;
	case 1:		//bottom
		p.y++;
		break;
	case 2:		//right
		p.x++;
		break;
	case 3:		//top
		p.y--;
		break;
	}
	return p;
}
void PrintItem(POS curP)
{
	int i,j;
	system("cls");//windows command
	for(i=0;i<10;i++)//行
	{
		for(j=0;j<10;j++)
		{
			if(i==curP.y && j==curP.x)//curP.y 表示y坐标,对应组下标的第一维,行
			{
				printf("@");
				continue;
			}

			if(item[i][j]==1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}


int main_maze(int argc, char* argv[])
{
	ElemType e;
	int setp=1;
	POS curPos=inPos;
	STACK *s =InitStack();

	PrintItem(inPos);
	do
	{
		if(IsPass(curPos))
		{
			e.sno=setp;//position  走了几步是OK的
			e.di=0;//direction
			e.seat=curPos;
			Push(s,&e);
			item[curPos.y][curPos.x]=2;//2表示走过了,再次就成为不可通过
			if(curPos.y ==outPos.y&& curPos.x==outPos.x)//当前是不是出口
			{
				PrintItem(curPos);
				printf("OK");
				getchar();//mypause
				break;
			}
			PrintItem(curPos);
			getchar();//mypause
			curPos=NextPos(curPos,0);
			setp++;//走了几步是OK的
		}else
		{
			Pop(s,&e);
			/*
			while(e.di==4 && !IsEmpty(s))//永远不可能e.di==4
			{
				item[curPos.y][curPos.x]=3;//都走不通
				Pop(s,&e);
			}
			*/
			if(e.di<3)
			{
				e.di++;
				Push(s,&e);
				curPos=NextPos(e.seat,e.di);

			}
		}
	}while(! IsEmpty(s));//后一定要加;号


	return 1;
}



