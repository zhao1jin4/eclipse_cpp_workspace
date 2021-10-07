namespace quiz_reverse
{

	#include<stdio.h>
	#include <string.h>
	void mysubstr(char*t,const char*s,int pos,int len)
	{
		while(len>0&&*s)
		{  *t=*(s+pos-1);
		t++;s++;len--;
		}
		*t='\0';
	}
	char  *f31(char*s)
	{   char  t[100];
		if  (strlen(s)==1)
		   return  s;
		mysubstr(t,s,1,1);
		mysubstr(s,s,2,strlen(s)-1);
		f31(s);
		return strcat(s,t);
	}


	int main(int  argc, char* argv[])
	{
		 char str[100]= "String";
			printf("%s\n",f31(str));
	}

}

