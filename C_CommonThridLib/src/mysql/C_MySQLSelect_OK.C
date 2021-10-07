
#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"
//#include <windows.h> //如是运行在windows 下MinGW还要加windows.h

namespace mysql_c
{

//对于libmysql.dll使用-l libmysql或者-lmysql,对于libmysql.lib只能使用-llibmysql,测试成功

//g++ -o mysql_conn C_MySQLSelect_OK.C  -I D:\Application\mysql-8.0.15-winx64\include -L D:\Application\mysql-8.0.15-winx64\lib   -llibmysql
//g++ -o mysql_conn C_MySQLSelect_OK.C  -I D:\Application\mysql-8.0.15-winx64\include -L D:\Application\mysql-8.0.15-winx64\lib  -l mysql
//windows 下用-l mysqlclient 不行的,win7 64位(mysql是64位的) 运行时报 找不到  LIBEAY32.dll

//g++ -o mysql_conn C_MySQLSelect_OK.C  -I ~/mysql-8.0.18-linux-glibc2.12-x86_64/include/ -L ~/mysql-8.0.18-linux-glibc2.12-x86_64/lib/  -l mysqlclient
//运行就找不到库 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/mysql-8.0.18-linux-glibc2.12-x86_64/lib  就可以了

//C 连接 MySQL OpenSUSE-leap-15.2 测试成功
//# /usr/local/mysql/bin/mysql_config --libs --cflags

int main (int  argc, char* argv[])
{

	char *host="localhost",*user = "root", *pwd = "root", *dbname = "mysql";
	unsigned int port=3306;
   char * sock="/tmp/mysql.sock"; //为何总报使用 /run/mysql/mysql.sock' 呢？
	//char * sock=NULL;
    //host=NULL;

    const char *query="select   *   from   user";

	MYSQL mysql;
	MYSQL_RES *mysql_ret;
	MYSQL_ROW mysql_row;
	MYSQL_FIELD * fd;
	unsigned long num_rows;
	int ret;
	mysql_init(&mysql);

	unsigned int timeout=7;
    mysql_options(&mysql,MYSQL_OPT_CONNECT_TIMEOUT,(const char * )&timeout); //连接超时时间

	if (mysql_real_connect(&mysql, host, user, pwd, dbname, port, sock, 0))//unix_socket,clientflag
	{
		printf("Connection   success!\n");
		ret = mysql_query(&mysql, query);
		printf("Effect rows is %lu\n",(unsigned long) mysql_affected_rows(&mysql));//只对update,insert,delete有效
		if (!ret)
		{
			printf("Query   Success!\n");
			mysql_ret = mysql_store_result(&mysql);
			if (mysql_ret != NULL)
			{
				int cols=mysql_num_fields(mysql_ret);
				printf("===========have %d fileds\n",cols);
				int i;
				for (i = 0; fd = mysql_fetch_field(mysql_ret); i++)
					printf("|%s|\t",fd->name);

				printf("\n");

				num_rows = mysql_num_rows(mysql_ret);
				if (num_rows != 0)
				{
					printf("=======have %d rows\n", num_rows);
					while (mysql_row = mysql_fetch_row(mysql_ret))
					{
						printf("|%s|\t|%s|\t\t\n", mysql_row[0],mysql_row[1]);
					}
				} else
				{
					printf("mysql_num_rows   Failed!\n");
					exit(-1);
				}
				mysql_free_result(mysql_ret);
				exit(0);
			} else
			{
				printf("Store   Result   Failed!\n");
				exit(-1);
			}
		} else
		{
			printf("Query   Failed!\n");
			exit(-1);
		}
	} else
	{
		printf("Connection   Failed\n");
		printf("Errorno=%d and  Error=%s\n",mysql_errno(&mysql),mysql_error(&mysql));
		exit(-1);
	}

	mysql_close(&mysql);
}
//DDL就不用 mysql_store_result
}

