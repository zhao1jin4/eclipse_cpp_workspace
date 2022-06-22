#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>


namespace regex
{

	/* 取子串的函数 */
	static char* substr(const char*str, unsigned start, unsigned end)
	{
	  unsigned n = end - start;
	  static char stbuf[256];
	  strncpy(stbuf, str + start, n);
	  stbuf[n] = 0;
	  return stbuf;
	}
	/* 主程序 */
	int main(int argc, char* argv[])
	{
	  char * pattern;
	  int x, z, lno = 0, cflags = 0;
	  char ebuf[128], lbuf[256];
	  regex_t reg;
	  regmatch_t pm[10];
	  const size_t nmatch = 10;

	  /* 编译正则表达式*/
	 // pattern = "[a-zA-Z0-9_\.]+@[a-zA-Z0-9-]+[\.a-zA-Z]+";//email
	  pattern = "(13[0-9]|15[0-9]|189)[0-9]{8}";//mobile phone NO
	  z = regcomp(&reg, pattern, cflags);
	  if (z != 0)
	  {
		regerror(z, &reg, ebuf, sizeof(ebuf));
		fprintf(stderr, "%s: pattern '%s' \n", ebuf, pattern);
		return 1;
	  }
	 // strcpy(lbuf,"abc@test.com");
	  strcpy(lbuf,"13012345678");


		/* 对每一行应用正则表达式进行匹配 */
		z = regexec(&reg, lbuf, nmatch, pm, 0);
		if (z == REG_NOMATCH)
		{
			 fprintf(stderr, "no match result !\n");
			return -1;
		}
		else if (z != 0)
		{
		  regerror(z, &reg, ebuf, sizeof(ebuf));
		  fprintf(stderr, "%s: regcom('%s')\n", ebuf, lbuf);
		  return 2;
		}
		/* 输出处理结果 */
		for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x)
		{
		  if (!x)
			  printf("%04d: %s\n", lno, lbuf);
		  printf("  $%d='%s'\n", x, substr(lbuf, pm[x].rm_so, pm[x].rm_eo));
		}

	  /* 释放正则表达式  */
	  regfree(&reg);
	  return 0;
	}

}

