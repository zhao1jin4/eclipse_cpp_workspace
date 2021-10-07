#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <limits.h>
//#include <ctype.h>

namespace stl_chinese  //stdlib.h
{
	void stdlib_cn_utf8_file()
	{
		//----单个中文处理 mblen mbtowc wctomb

		setlocale (LC_ALL, "chs");  //设置为简体中文环境
		//setlocale (LC_ALL, "enu");  //设置为英文环境
		int max=MB_CUR_MAX;//LC_ALL=chs时是2 , LC_ALL=enu时是1
		int count=mblen("中",max);//LC_ALL=chs时是2 , LC_ALL=enu时是1
		printf ("one CNS character lenght: %d\n",count);//1或2

		//----	char* 单个中文 ->wchar_t ,失败?????????
		wchar_t *expect=L"国";
		wchar_t wc;
		char* cn_char = "国";
		int len = mbtowc (&wc, cn_char, MB_LEN_MAX);//MB_LEN_MAX固定为2,LC_ALL=enu时len是1,/LC_ALL=chs时len是2
		bool isRight= (wc == expect[0]);
		wprintf(L"char* Single CHS Character ->wchar_t , result:%lc, effected:%d ,isRight:%d\n",wc,len,isRight);

		//---- wchar_t 单个中文 -> char* ,失败?????????
		wchar_t *from=L"国";
		char to[MB_LEN_MAX + 1];
		len = wctomb (to, from[0]);
		to[len] = '\0';
		isRight=( (to[0]==cn_char[0]) && (to[1]==cn_char[1]) );
		printf("wchar_t Single CHS Character-> char* ,result:%s ,effected:%d,isRight:%d\n",to,len);

		//----英文 wchar_t 处理  mbstowcs wcstombs,不可有中文
		//---mblen
		char sBuf[20];
		memset(sBuf,0,20);
		strcpy(sBuf, "中华人民共和国");
		size_t sSize=strlen(sBuf);//21不对?????

		char* compare="中华人民共和国";
		int isEqual=strcmp(compare,sBuf);//0  是一样的

		int dSize=mblen(sBuf,20);//不对?????
		mbstate_t state;
		dSize=mbrlen(sBuf,20,&state);//不对?????


		//---mbstowcs
		wchar_t * wsExpect=L"CHINA";
		char * enStr="CHINA";
		dSize=strlen(enStr);
		wchar_t dBuf[dSize  + 1 ] ;//多一个空间存放终止符
		wmemset(dBuf, 0, dSize + 1);//wmemset,最后一个是\0终止,在 wchar.h文件中
		int nRet=mbstowcs(dBuf, enStr, sSize);
		wprintf(L"char* ENU String, MUST not have CHS->  wchar_t* ,result : %ls\n", dBuf);//CDT终端编码显示不正常

		//---wcslen,wcstombs
		wchar_t * wFrom=L"Chinese";
		int wLen=wcslen(wFrom);//7 正常
		char  byte[wLen*2 +1];
		byte[wLen*2 +1]='\0';
		nRet=wcstombs(byte,wFrom,wLen*2);//不可有中文,因为放不下
		printf("wchar_t* ENU String,MUST not have CHS->char* ,result : %s\n", byte);
	}

   int main(int argc, char* argv[])
   {
	   //setlocale (LC_ALL, "chs");  //设置为简体中文环境
	   //setlocale (LC_ALL, "enu");  //设置为英文环境

	   //有时,有中文就不显示,有时wprintf不显示,编译器有关
	   wprintf (L"wprintf__中文 \n");//wprintf不就显了???????  , Cyginw
	   printf ("printf__中文 \n");

	   //stdlib_cn_utf8_file();

	   return 0;
   }


}
