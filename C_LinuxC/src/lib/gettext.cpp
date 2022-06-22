#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <libintl.h> //intl= international

namespace lib_gettext
{
	#define _(string) gettext(string)

	int main (int argc, char *argv[])
	{
		setlocale (LC_ALL, "");//LC_ALL全部的locale, LC_MESSAGES是本地语言的locale

		textdomain ("gettext_test");//告诉该程序到gettext_test.mo中去找其它语音的信息。

		bindtextdomain ("gettext_test", "language");// 到当前目录中的language目录下去找


		if(argc < 2)
		{
			printf(_("not enough parameter!\n"));
			printf(_("usage: %s username\n"), argv[0]);
			exit(1);
		}

	  printf (_("welcome to world of gettext, %s!\n"), argv[1]);
	  return 0;
	}
	//xgettext --keyword=_ -o gettext_test.po gettext_test.c    生成gettext_test.po
};



