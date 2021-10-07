#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <stddef.h>

//using namespace std;

namespace stl_c
{

int C_readWriteFileTest()
{

	/*
r(read): 读
w(write): 写 ,存在覆盖
a(append): 追加 ,文件不存在则建立

r+ 		读写打开存在文件
w+ 		读写建立文件,存在覆盖
a+ 		文件不存在则建立,写只在尾,但可fseek,rewind到其它位置去读

t(text): 文本文件，可省略不写
b(banary): 二进制文件

	 */

	FILE *fp;
	if((fp=fopen("d:/temp/my.txt","wt"))==NULL)//
	{
		printf("不能打开文件");
		exit(0);
	}

	char str[30];
	scanf("%s",&str);
	fwrite(&str,sizeof(char),strlen(str),fp);
	fclose(fp);


	if((fp=fopen("d:/temp/my.txt","rt"))==NULL)//
	{
		printf("不能打开文件");
		exit(0);
	}
	fread(&str,sizeof(char),strlen(str),fp);
	fclose(fp);

	printf("从文件中读到的内容:%s",str);
	//fflush(stdout);

	return 1;
}
void stringMathFunc()
{
//
//	char str1[30];
//	gets(str1);//不认？？？
//	printf("%s\n",str1);


	char chars[]="Hello"; //字符串常量
	printf("%d",sizeof(chars));


	char *str="Linux was first";
	char *t1="Air";//in
	printf("第一次出现包含子串中的字符的位置%d\n",strcspn(str,t1));//1,split n,

   char *string1 = "1234567890";
   char *string2 = "A123DC8";
   int length=strspn(string1, string2);//3
   printf("第一次出现与字串不相同的索引:%d\n", length);


	char input[16] = "abc,d~123,tt";
	char *p;
	p = strtok(input, ",~");//string token
	while(p)
	{
		printf("以,分隔的:%s\n", p);
		p = strtok(NULL, ",~");//第二次开始要设置为NULL,才会对第一次的值做多次
	}


	printf("compare is:%d\n",strcmp("0","1"));//第一个 大于  第二个 return 1


}
int memory()
{
	char src[5];
	memset(src,'w',4);//将a里的值全部变成'w'
	src[4]='\0';
	char dest[5];
	memcpy(dest,  src,sizeof(src));
	printf("复制完成后：%s\n",dest);

	char * data = (char*)malloc(3);
	data[0]='a';
	data[1]='b';
	data[2]='\0';
	printf("malloc的内存：%s\n",data);

	char *newData=(char*)realloc(data,4);
	if(newData != NULL)
	{
		newData[2]='c';
		newData[3]='\0';
		printf("realloc的内存：%s\n",newData);
		free(newData);
	}else
		free(data);

	return 1;
}
void cLibrary()
{
	// http://www.cplusplus.com/reference/clibrary/


//-------------------------------assert.h
	int * myInt = NULL;
	assert (myInt==NULL);
	//assert (myInt!=NULL);

//-------------------------------ctype.h c是char的缩写
	int i;
	char str[]="c3po...c3po";
	i=0;
	while (isalnum(str[i]))//是否为字母数字
		i++;
	printf ("从开始处一共有 %d个有效     字母数字.\n",i);

	i=0;
	while (isalpha(str[i]))//是否为字母
		i++;
	printf ("从开始处一共有 %d个有效      字母.\n",i);

	i=0;
	char str11[]="first line \n second line \n";
	while (!iscntrl(str11[i]))//是否为控制字符, \n为控制字符
	{
		putchar (str11[i]);
		i++;
	}

	char str22[]="1776ad";
	  int year;
	  if (isdigit(str22[0]))//是否为数字
	  {
	    year = atoi (str22);
	    printf ("The year that followed %d was %d.\n",year,year+1);
	  }

	  //isgraph(c);//是否为可正常显示的字符
	  //islower是否是小写
	  //isprint 是否可见的
	  //ispunct 是否为标点
	  //isspace是否为空白
	  //isupper是否为大写字母
	  //isxdigit是否为16进制数
	  //tolower,toupper转换大小写
//-------------------------------errno.h
	  //cerrno 当程序错误时,这个变量会被赋值
//-------------------------------float.h 不知道做什么用????

//-------------------------------iso646.h 可以不包含,默认是加入的像stdlib.h
//	  macro	operator//定入以下的宏
//	  and		&&
//	  and_eq	&=
//	  bitand	&
//	  bitor		|
//	  compl		~
//	  not		!
//	  not_eq	!=
//	  or		||
//	  or_eq		|=
//	  xor		^
//	  xor_eq	^=

	 int a=1;
	 if (a==1 bitor a++==5) //or
		 printf("成立a=%d\n",a);
	  else
		 printf("不成立a=%d\n",a);

//-------------------------------limits.h
	 int max =INT_MAX;
	 printf("%d\n",max);
	 max++;
	 printf("溢出%d\n",max);


//-------------------------------locale.h  & time.h
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );//把当前的时间截写入
	timeinfo = localtime ( &rawtime );//转为当地时间,可以读年月日等

	char buffer [80];
	strftime (buffer,80,"%Y-%m-%d %H:%M:%S , %Z ",timeinfo);//把日期转字串,%Y-%m-%d %H:%M:%S  ,%X表示%H:%M:%S ,%Z 为CST或China Standard Time
	printf ("Date is: %s\n",buffer);

	printf ("Locale is: %s\n", setlocale(LC_ALL,"") );//"", 环境默认的locale,"C"是最小的locale

	struct lconv * lc;
	lc = localeconv ();
	printf ("Currency symbol is: %s\n-\n",lc->currency_symbol);//货币符号 ￥,		$
	printf ("International Currency Symbol: %s\n",lc->int_curr_symbol);//CNY,	USD

//-------------------------------math.h

	printf("%f\n",exp(3));//e的3次方
	printf("%f\n",pow(10.0,3));//10的3次方
	printf("%e\n",101.3);//%e 科学计算法输出
	printf("%d\n",abs(-8.6));
	printf("%f\n",ceil(-8.6));//-8,ceil 向大了取
	printf("%f\n",ceil(8.6));//9
	printf("%f\n",floor(-8.6));//floor 向小了取
	printf("%f\n",floor(8.6));
	printf("%f\n",sqrt(64));//开平方根
	printf("%f\n",log(30));//以e为底的对数
	printf("%f\n",log10(100));//以10为底的对数
	printf("%f\n",sin(M_PI/2));//sin,Pai=3.14

//-------------------------------stddef.h
	struct mystruct {
	  char singlechar;
	  char arraymember[10];
	  char anotherchar;
	};
	  printf ("offsetof(mystruct,singlechar) is %d\n",offsetof(mystruct,singlechar));//offset of,返回 size_t 表示字段在结构体中的位置
	  printf ("offsetof(mystruct,arraymember) is %d\n",offsetof(mystruct,mystruct::arraymember));//1,写法多样
	  printf ("offsetof(mystruct,anotherchar) is %d\n",offsetof(mystruct,anotherchar));//11

	  //两个指针减法操作的结果是  ptrdiff_t,有可能是负数
	  int buff[4];
	  ptrdiff_t diff = (&buff[3]) - buff; // diff = 3
	  printf ("两者之间有%d个字节\n",diff);
	  diff = buff -(&buff[3]); //  -3
	  printf ("两者之间有%d个字节\n",diff);

//-------------------------------stdint.h   C++11
//-------------------------------stdio.h
	  FILE * f=tmpfile(); //以wb+ 模式建立一个临时文件,可以保证文件名不是已有的,并打开,在close时删除
	  //intf ("文件名是: %s\n",f->_tmpfname);//Cyginw编译器没有这个成员
	  char * content ="testABC中国";
	  int len=strlen(content);
	  fwrite((void*)content,1,len,f);
	  fclose(f);

	  char bufferFile [L_tmpnam];//长度最小值 宏L_tmpnam
	  tmpnam (bufferFile);//返回一个文件名
	  printf ("带参的临时文件名:%s\n",bufferFile);
	  char * pointer = tmpnam (NULL);//如果传NULL使用返回值,下次调用会覆盖这部分区域
	  printf ("NULL参的临时文件名: %s\n",pointer);


	  char * from="d:/temp/abc.tmp";
	  char * to="d:/temp/abc123.tmp";
	  if(rename(from,to)!=0)  //文件重命名
	  {
		  printf (" errno:%d,%s\n",errno,strerror(errno));//显示errno对应的消息
		  //perror("文件重命名 失败原因为--");//最近一次错误的解释,
	  }
/*	  if(remove(to))//删除文件
	  {
		   printf (" errno:%d,%s\n",errno,strerror(errno));
		  //perror("删除文件  失败原因为--");
	  }

	  freopen ("d:/temp/Clog.txt","w",stdout);//先关闭myfile.txt与stdout关联,再建立单向关联,向stdout写操作,改为向文件写,
	  printf ("This sentence is redirected to a file.");
	  printf ("#------文件中的内容,为后面测试用.");
	  fclose (stdout);

	   FILE* openFile=fopen("d:/temp/open.txt","r");
	   FILE* reopenFile=freopen ("d:/temp/reopen.txt","r",openFile); //从openFile中读 修改为 从reopen.txt中读 , r和w混用无效果
	   if(openFile!=NULL || openFile!=NULL)
	   {
		   char text[20];
		   fread((void*)text,1,20,openFile);
		   printf ("读到的是:%s",text);
		   fclose (openFile);
		   fclose (reopenFile);
	   }

		//void setbuf ( FILE * stream, char * buffer );//full,为文件指定缓冲区,如为NULL,则禁用缓冲,要在open之后,操作之前来调用,必须是数组,最小为 BUFSIZ
		//int setvbuf ( FILE * stream, char * buffer, int mode, size_t size );//line 缓冲, mode指定_IOLBF,如果字符为换行符,清缓存
		setvbuf(stdout,NULL,_IONBF,0);//_IONBF表示不缓存

		//fprintf(),fscanf(),sprinf(),sscanf(),
		//vprintf 使用va_list做参数,使用stdarg.h做处理 ,还有vfprintf,vsprintf
		//%-10.10s : 表示左对齐 (-), 最小字符数(10), 最大字符数(.10),  (s) .
		printf("%-*s", 10, "abc");// 表示输出字符串左对齐输出10，如果字符串不够20个，以空格补齐
		puts("请输入一串字符\n");

		char ch= getc(stdin);//fgetc
		putc(ch,stdout);//fputc 可能EOF返回

		char input[1024];
		gets(input);//从stdin中读一行(\n结束)字串存到str,NULL,可用feof,ferror
		puts(input);//向stdout中输出
		//对应的有fgetc,fgets
		puts("请输入一个字符\n");
		ch=getchar();//从stdin
		putchar(ch);//向stdout

 	 */
		FILE * pFile;
		  int c;
		  char buf [255];
		  pFile = fopen ("d:/temp/myfile.txt","rt");
		  if (pFile==NULL) perror ("Error opening file");
		  else {
		    while (!feof (pFile))
		    {
		      c=getc (pFile);
		      if (c == '#')
		        ungetc ('@',pFile); //把@放回内存中当前位置(对前面已经getc),下次就可以读到,并不会修改文件
		      else
		    	ungetc (c,pFile);
		      fgets (buf,255,pFile);
		      fputs (buf,stdout);
		      memset(buf,0,255);

		    }
		  }

//-------------------------------stdlib.h
		float val=atof ("2.3");//ascii to float
		printf("atof 结果%f\n",val*2);
		//对应有atoi,atol,

		char * pEnd;
		double d1 = strtod ("12.3def",&pEnd);//第二个参数返回解析错误的字串
		printf("strtod 结果%f,终止字串%s\n",d1 * 2,pEnd);
		//对应的有strtol,strtoul


		int r=0;
		for(int i=0;i<3;i++)
		{
			r=rand();
			printf("10-100的随机数%d\n" ,r%10+90);//10-100
		}

		//calloc和malloc,参数不同
		printf ("操作系统环境变量path: %s\n",getenv ("PATH"));//操作系统环境变量
		i=system ("dir");//执行操作系统命令,返回值0表示执行成功
		printf ("The value returned was: %d.\n",i);

		div_t divresult;
		divresult = div (38,5);//同样的还有ldiv(long div)
		printf ("38 div 5 => %d, remainder %d.\n", divresult.quot, divresult.rem);

		long res=labs(-23423l);//long abs
		printf ("labs:%d\n",res);

//-------------------------------string.h
		char test[] = "memmove can be very useful......";
		puts (test+20);
		puts (test+15);
		memmove (test+20,test+15,11);//是复制不会把源删除，内存重叠是可以的，memcpy　内存不能重叠
		puts (test);

		char str2[5];
		memset(str2,'x',sizeof(str2));
		strncpy (str2,test,4); //strncpy多一个长度参数,要手动加'\0'
		str2[4]='\0';
		puts (str2);

		char str3[10];
		memset(str3,'x',sizeof(str3));
		char m[3];
		memset(m,'x',sizeof(m));
		m[0]='a';
		m[1]='b';
		m[2]='\0';

		strcpy (str3,"this ");//strcpy会把'\0'也复制,
		strcat (str3,m);//strcat　把第二个字串符加到第一个字串后面，会把第一个串'\0'覆盖,第二个串要有'\0'
		puts (str3);

		char m1[3];
		memset(m1,'x',sizeof(m1));
		m1[0]='u';
		m1[1]='v';
		strncat (str3,m1,2);// strncat 多一个长度参数,会自动加'\0'
		puts (str3);

		setlocale(LC_ALL,"chs");
		strcoll("噢","啊");//使用 setlocale 比较大小,即中文的汉语拼音
		//还有memcmp,strcmp,strncmp


		//size_t strxfrm ( char * destination, const char * source, size_t num );//setlocale,transform and copy
		//可传destination为NULL,num为0,只要返回的汉字的长度
		setlocale(LC_ALL,"C");
		//char* source = "1234567890 abc";
		char* source = "中国";
		char des[100];
		len = strxfrm(des, source, 50); //和strcpy很像,有什么特别的用途吗??
		printf("len:%d\n",len);
		printf("des:%s\n",des);

		//---
		char * pch;
		char str_chr [] = "Example string";
		pch = (char*) memchr (str_chr, 'p', strlen(str_chr));//和bsearch很像
		if (pch!=NULL)
			printf ("'p' found at position %d.\n", pch- str_chr +1);
		else
			printf ("'p' not found.\n");
		//---

		char str_tosearch[] = "This is a sample string";
		char * pch_found;
		pch_found=strchr(str_tosearch,'s');//chr=character 在内存中搜索char,返回找到的所在内存地址
		while (pch_found!=NULL)
		{
			printf ("found at %d\n",pch_found - str_tosearch+1);
			pch_found=strchr(pch_found+1,'s');
		}
		//---
		pch_found=strrchr(str_tosearch,'s'); //只找最后一次现char的地址
		printf ("Last occurence of 's' found at %d \n",pch_found - str_tosearch +1);
		//--
		char key[] = "aeiou";
		printf ("Vowels in '%s': ",str_tosearch);
		pch_found = strpbrk (str_tosearch, key);//和strchr 一样只是可以传多个char
		while (pch_found != NULL)
		{
			printf ("%c " , *pch_found);
			pch_found = strpbrk (pch_found+1,key);
		}
		//--
		printf("\n");
		pch_found = strstr (str_tosearch,"sample");//substring 子串的地址
		strncpy (pch_found,"simple",6);//修改字串
		puts (str_tosearch);


		//-------------------------------time.h
		//strftime
		int t=clock();
		printf ("从程序启动到现在花费了%d clicks ,%f 秒\n",t,((float)t)/CLOCKS_PER_SEC);


		//	time_t start,end;
		//	char szInput [256];
		//	printf ("Please, enter your name: ");
		//	time (&start);
		//	gets (szInput);
		//	time (&end);
		//	double dif = difftime (end,start);//计算两个时间点有多少秒
		//	printf ("Hi %s.\n", szInput);
		//	printf ("It took you %.2lf seconds to type your name.\n", dif );


		//asctime ,ctime 只是使用特定的格式 Www Mmm dd hh:mm:ss yyyy

		time_t timestamp;
		time ( &timestamp );
		struct tm * tm_now = gmtime ( &timestamp );//转成GMT时间
		printf ("GMT 北京+8 时间:  %02d:%02d\n", (tm_now->tm_hour + 8)%24, tm_now->tm_min);//%02d可显示00,而不是一个0


	}
	void makeTime() //不知道为什么放在 cLibrary方法中printf不正常??可能是有其它的错误
	{
		time_t timestamp;
		struct tm * t_info;
		time  ( &timestamp );
		t_info = localtime ( &timestamp );
		t_info->tm_year = 2012 - 1900;//从1900 年开始
		t_info->tm_mon = 9 - 1;//值的范围0-11
		t_info->tm_mday = 32;
		time_t x=  mktime( t_info );//会忽略 tm_wday 和 tm_yday 并设置成正确的值 ,其它属性没设置范围的限制,像tm_mday没以31天或更大
						  //功能和localtime 反的
		printf ("星期%d", t_info->tm_wday);//值的范围0-6,0是星期日

	}

	int main(int argc,char* argv[] )
	{
		//C_readWriteFileTest();
		//stringMathFunc();
		//memory();
		cLibrary();
		//makeTime();

		return 1;
	}
}
