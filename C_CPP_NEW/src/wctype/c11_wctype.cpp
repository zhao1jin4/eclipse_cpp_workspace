
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

namespace c11_wctype
{

	int main(int  argc, char* argv[])
	{
		int result=iswalnum(L'a');//wal=world alpha
		result=iswalnum(L'中');
		result=iswdigit(L'3');
		result=iswdigit(L'A');//a-f或者A-F,十六进制
		//以上返回0表示假,正数表示真

		 int i=0;
		 const wchar_t *str = L"Test String.\n"; //vc一定要加const
		  wchar_t c;
		  wctype_t check = wctype("lower");
		  /*
		  "alnum"	alphanumerical character	iswalnum
		  "alpha"	letter character	iswalpha
		  "blank"	blank character	iswblank
		  "cntrl"	control character	iswcntrl
		  "digit"	decimal digit character	iswdigit
		  "graph"	character with graphical representation	iswgraph
		  "lower"	lowercase letter character	iswlower
		  "print"	printable character	iswprint
		  "punct"	punctuation character	iswpunct
		  "space"	white-space character	iswspace
		  "upper"	uppercase letter character	iswupper
		  "xdigit"	hexadecimal digit character	iswxdigit
		  */

		  wctrans_t trans = wctrans("toupper");//只可传tolower和toupper,同towlower和	towupper
		  while (str[i])
		  {
		    c = str[i];
		    if (iswctype(c,check))
		    	c = towctrans(c,trans);
		    putwchar (c);
		    i++;
		  }

		return 0;
	}

}

