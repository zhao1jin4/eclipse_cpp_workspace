#include <string.h>
#include <stdio.h>

#include <stdlib.h>
#include <wchar.h>
#include <locale.h>


namespace c11_wchar
{

	void readChineseFile()
	{
		FILE * pFile;
		wint_t wc;//wint_t类型
		int n = 0;
		pFile=fopen ("c:/temp/c_file.txt","r");//文件名不支持中文 ????????
		if (pFile!=NULL)
		{
			do
			{
				wc = fgetwc (pFile);//fgetwc函数
				if (wc == L'$') //加L
					n++;
				wprintf (L"%lc",wc);//是%lc
			}while(wc != WEOF);//WEOF
			fclose (pFile);
			wprintf (L"\nThe file contains %d dollar sign characters ($).\n",n);//wprintf函数
		}
	}
	void wchar_number()
	{
		//----------wchar_t 与　数　转换
		wchar_t result[20];
		//swprintf(result,L"%ld",-123.33);//MinGW
		swprintf(result,20,L"%ld",-123.33);//Cygwin
		wprintf (L"number  ->　wchar_t* ,use  swpritnf ,result:%ls \n",result);

		double num=wcstod(L"-456.33",NULL);//wchar_t ->  double数字
		wprintf (L"wchar_t* -> double: %lf\n",num);

		long int res=wcstol(L"123",NULL,10);//10进制
		wprintf (L"wchar_t* -> long1: %ld\n",res);

		wchar_t data[10]={L"456"};
		res=wcstol(data,NULL,10);
		wprintf (L"wchar_t* -> long2: %ld\n",res);

	}
	void wchar_method()
	{
		//--------wchar_t 相关函数
		//wchar_t * cn=L"中华人民共和国";//是不可变的,不能用wmemset,过时的用法
		wchar_t cn[8]=L"中华人民共和国";//可用wmemset
		int len=wcslen(cn);//7
		wprintf (L"wchar_t  wcslen :%ld \n",len);

		wchar_t zero='\空';
		wchar_t zero1=L'-';
		wchar_t buffer[20];
		wmemset(buffer,zero,20);
		//wmemset(cn,zero,20);//OK

		//wcscpy(buffer,cn);//OK
		wmemcpy(buffer,cn,len * 2);//OK,复制

		int isequal = wcsncmp (buffer,cn,len+1 );//0  ,前n位比较
		//int isequal=wmemcmp(cn,buffer,len+1);//0

		wprintf (L"source: %ls \n",cn);//不显示????
		wprintf (L"target: %ls \n",buffer);//不显示????

	}

	void wchar_char()
	{
		mbstate_t  state;
		char  cn[30];
		strcpy(cn,"中华人民共和国");
		int len=mbrlen(cn,30,&state);//-1 错误???

		//---单个 btowc
		wchar_t w=btowc('c');//byte to wchar,要当于L,是动态的
		wprintf (L"char ->wchar_t : %lc\n",w);

		//---单个 wctob
		const wchar_t* wStr=L"test";
		int c=(wStr[0]);	//MinGW对wctob不可编译,Cygwin可以编译
		char expectC='c';//结果不对??????????
		printf ("wchar_t ->char : %c ,Right:%d \n",c,(expectC==c));

		//-----mbsrtowcs      char* 中文  ->  wchar_t *的转换
		//const char *str      = "Hello世界";
		const char *str        = "世界Hello";//9+1
		int str_len=strlen(str);//怎么会是11 ??????
		wchar_t    *wstr = (wchar_t *)calloc(str_len, sizeof(wchar_t));	//分配空间
		//wchar_t wstr[str_len];
		mbstate_t  state1;
		memset(&state1, 0, sizeof(state1));
		int rtn=mbsrtowcs(wstr, &str, str_len, &state1);//多个r,restartable
		printf("char* CNS  -> wchar_t* : %ls\n", wstr);
		free(wstr);

		//-----wcsrtombs  wchar_t*必须英文 ->  char*
		char to[50];
		const wchar_t* from=L"Chinese";
		mbstate_t state2;
		rtn=wcsrtombs(to,&from,50,&state2);//不支持中文,必须英文
		printf("wchar_t* MUST ENU  ->  char*  : %s\n", to);

	}
	int main(int  argc, char* argv[])
	{

		//setlocale (LC_ALL, "chs");  //设置为简体中文环境
		//setlocale (LC_ALL, "enu");  //设置为英文环境

		//有时,有中文就不显示,有时wprintf不显示,编译器有关
	   wprintf (L"wprint_中文 \n");//有中文就不显示了???????  ,
	   printf ("_printf中文 \n");

		//readChineseFile();
		//wchar_number();
		//wchar_char();
		//wchar_method();
		return 0;
	}

}

