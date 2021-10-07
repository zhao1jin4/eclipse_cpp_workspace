#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

namespace stl_arg
{
	int testarg(const char * cstrParams, ...)
	{
		int count, i;
		va_list marker;
		count = strlen(cstrParams);
		printf("Total Params: %d\n", count);
		va_start( marker, cstrParams);//信息存到va_list,表示cstrParams参数后面的做为动态参数
		for (i = 0; i < count; i++)
		{
			const char * cstrStrParam;
			int nNumberParam;
			switch (cstrParams[i])
			{
			case 'I':
				nNumberParam = va_arg( marker, int);//va_arg 是会va_list中存入按 int 顺序取
				printf("Param %d: int type, value = %d\n", i, nNumberParam);
				break;
			case 'S':
				cstrStrParam = va_arg( marker, const char *);
				printf("Param %d: string type, value = '%s'\n", i, cstrStrParam);
				break;
			}
		}
		va_end( marker);//释放va_list内存
		return 0;
	}

	void PrintFloats ( int amount,float one, ...)
	{
	  int i;
	  double val;
	  printf ("Floats passed: ");
	  va_list vl;
	  va_start(vl,one);//表示one参数后面的做为动态参数
	  for (i=0;i<amount-1;i++)
	  {
	    val=va_arg(vl,double);
	    printf ("\t%.2f",val);
	  }
	  va_end(vl);
	  printf ("\n");
	}


	void WriteFormatted (char * format, ...)
	{
	  va_list args;
	  va_start (args, format);
	  vprintf (format, args); //还有vfprintf,vsprintf
	  va_end (args);
	}

	int main(int argc, char **argv)
	{
		//PrintFloats (3,3.14159,2.71828,1.41421);
		//testarg("ISI", 3,  "3 & 4",4);
		WriteFormatted ("Call with %d variable %s.\n",2,"arguments");
		return 1;
	}
}

