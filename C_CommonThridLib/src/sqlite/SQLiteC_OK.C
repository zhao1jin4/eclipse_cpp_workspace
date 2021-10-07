//MinGW要调试的话,必须把sqli3.dll放在PATH中可以找到才行

/*

namespace sqlite
{
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
//#pragma comment(lib, "sqlite.lib")//我把sqlite编译成了一个静态的lib文件。
// 源码安装sqlite 不要删make的文件夹，eclipse-debug时可以打开源码.c

//#define DB_FILE "/home/zhaojin/sqliteDB"
#define DB_FILE "c:/temp/sqliteDB"

void error_exit(sqlite3 *db, char *message)
{
	fprintf(stderr, "Error on %s: %s\n", message, sqlite3_errmsg(db));
	sqlite3_close(db);
	exit(EXIT_FAILURE);
}


void createTable()
{
	sqlite3 * handle;
	int status;
	sqlite3_stmt *stmt_sel;
	sqlite3_stmt *stmt_insert;


	char * error_msg;

	const char * z;
	char ** resultSet;
	int nrow = 0, ncolumn = 0;

	status=	sqlite3_open(DB_FILE, &handle); //文件没有会自动创建的
	//status=sqlite3_open_v2("sqliteDB", &handle,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE|SQLITE_OPEN_FULLMUTEX ,vfs_name);
	if (status != SQLITE_OK || handle == NULL)
		error_exit(handle,"open database");




		//===========create table和insert into   OK
		status = sqlite3_exec(handle, "BEGIN EXCLUSIVE TRANSACTION", NULL, NULL, &error_msg);//独占
		while(1)
		{
			if (status == SQLITE_OK) break;
			if (status != SQLITE_BUSY) error_exit(handle, "BEGIN EXCLUSIVE TRANSACTION");
			//sleep(1);//linux
		}
		sqlite3_exec(handle,"create table student (id int,name varchar(20))",0,0,&error_msg);
		sqlite3_exec(handle,"insert into student(id,name)values(1,'zhaojin')",0,0,&error_msg);
		sqlite3_exec(handle,"insert into student(id,name)values(2,'李')",0,0,&error_msg);
		sqlite3_exec(handle,"insert into student(id,name)values(3,'王')",0,0,&error_msg);
		status = sqlite3_exec(handle, "COMMIT TRANSACTION", NULL, NULL, &error_msg);//提交，解锁
		if (status != SQLITE_OK) error_exit(handle, "COMMIT TRANSACTION");
		//===========OK




	sqlite3_finalize(stmt_sel);
	sqlite3_finalize(stmt_insert);
	sqlite3_free(error_msg);
	sqlite3_close(handle);

}


void BindInsert()
{
	sqlite3 * handle;
	int status;
	sqlite3_stmt *stmt_sel;
	sqlite3_stmt *stmt_insert;


	char * error_msg;

	const char * z;
	char ** resultSet;
	int nrow = 0, ncolumn = 0;

	status=	sqlite3_open(DB_FILE, &handle); //文件没有会自动创建的
	//status=sqlite3_open_v2("sqliteDB", &handle,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE|SQLITE_OPEN_FULLMUTEX ,vfs_name);
	if (status != SQLITE_OK || handle == NULL)
		error_exit(handle,"open database");



		//=============================insert 数据  OK
	#define SQL_INSERT "insert into student values(:myid,:myname)"//;号可有可无，也可以用？
		status = sqlite3_prepare(handle,SQL_INSERT,strlen(SQL_INSERT),&stmt_insert,&z);
		if (status != SQLITE_OK) error_exit(handle, "sqlite3_prepare");

		int	id_index = sqlite3_bind_parameter_index(stmt_insert, ":myid");//根据占位符号，得到对应的索引位置,:myid也可以用？
		int name_index = sqlite3_bind_parameter_index(stmt_insert, ":myname");

		//status=sqlite3_bind_int(stmt_sel,id_index,1);//不能是int--sqlite不认int ,只认字串
		status=sqlite3_bind_text(stmt_insert,id_index,"10",sizeof("10"),SQLITE_TRANSIENT);//text用SQLITE_TRANSIENT   blob用SQLITE_STATIC
		//sqlite3_bind_blob(stmt, t_index, value, strlen(value), SQLITE_STATIC);//BLOB类型,表示0从来不改变，从来不会被销毁
		if (status != SQLITE_OK) error_exit(handle, "sqlite3_bind_text/mydi");


		status=sqlite3_bind_text(stmt_insert,name_index,"zhaojin",sizeof("zhaojin"),SQLITE_TRANSIENT);//对text
		if (status != SQLITE_OK) error_exit(handle, "sqlite3_bind_text/myname");

		status=sqlite3_step(stmt_insert);
		if ( status!=SQLITE_DONE) error_exit(handle, "step");//SQLITE_DONE 说明没有查询结果，或者insert 成功
	//----------





	sqlite3_finalize(stmt_sel);
	sqlite3_finalize(stmt_insert);
	sqlite3_free(error_msg);
	sqlite3_close(handle);

}
void selectData()
{
	sqlite3 * handle;
	int status;
	sqlite3_stmt *stmt_sel;
	sqlite3_stmt *stmt_insert;


	char * error_msg;

	const char * z;
	char ** resultSet;
	int nrow = 0, ncolumn = 0;

	status=	sqlite3_open(DB_FILE, &handle); //文件没有会自动创建的
	//status=sqlite3_open_v2("sqliteDB", &handle,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE|SQLITE_OPEN_FULLMUTEX ,vfs_name);
	if (status != SQLITE_OK || handle == NULL)
		error_exit(handle,"open database");


	//=============================select 数据

	 const char* SQL_SEL="select id ,name from student where id=:myid and name=:myname;";

	//status = sqlite3_prepare_v2(handle,SQL_SEL,strlen(SQL_SEL),&stmt_sel,&z);
	status = sqlite3_prepare(handle,SQL_SEL,strlen(SQL_SEL),&stmt_sel,&z);
	if (status != SQLITE_OK) error_exit(handle, "sqlite3_prepare");

	int	id_index = sqlite3_bind_parameter_index(stmt_sel, ":myid");
	int name_index = sqlite3_bind_parameter_index(stmt_sel, ":myname");

	int id_value=10; //=======num====== 如数据库中只插入过int，用int也可以查到
	//char * id_value="a001";

	char *  name_value="张";

	status=sqlite3_bind_int(stmt_sel,id_index,id_value);//=======num======
	//status=sqlite3_bind_text(stmt_sel,id_index,id_value,strlen(id_value),SQLITE_TRANSIENT);
	if (status != SQLITE_OK) error_exit(handle, "sqlite3_bind_text/mydi");

	status=sqlite3_bind_text(stmt_sel,name_index,name_value,strlen(name_value),SQLITE_TRANSIENT);//对text
	if (status != SQLITE_OK) error_exit(handle, "sqlite3_bind_text/myname");

	//status=sqlite3_step(stmt_sel); //	第一次就DONE   --  debug用，FAIL
	//if (!(status == SQLITE_ROW || status==SQLITE_DONE)) error_exit(handle, "step");

	while(sqlite3_step(stmt_sel)==SQLITE_ROW)//
	{
			char * name=sqlite3_column_text(stmt_sel,1);

			int id=sqlite3_column_int(stmt_sel,0);//=======num=====
			printf("id=%d \t name=%s \n",id,name); //======num=====

			//char *   id=sqlite3_column_text(stmt_sel,0);//0开始的第一个段
			//printf("id=%s \t name=%s \n",id,name); //
	}

	sqlite3_finalize(stmt_sel);
	sqlite3_finalize(stmt_insert);
	sqlite3_free(error_msg);
	sqlite3_close(handle);

}
void selectMetaData()//OK
{
	sqlite3 * db;
		int result;
		char * errmsg = NULL;
		char **resultSet;
		int nRow, nColumn;
		int i, j;
		int index;

		result = sqlite3_open(DB_FILE, &db);
		if (result != SQLITE_OK)
		{
			return ;
		}

		result = sqlite3_get_table(db, "select * from student", &resultSet, &nRow, &nColumn, &errmsg);

		if (SQLITE_OK == result)
		{

			index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
			printf("查到%d条记录\n", nRow);
			for (i = 0; i < nRow; i++) //   3
			{
				printf("第 %d 条记录\n", i + 1);
				for (j = 0; j < nColumn; j++)  //2
				{
					printf("字段名:%s  > 字段值:%s\n", resultSet[j], resultSet[index]);
					++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
				}
				printf("-------\n");
			}


			int k;
			for (k = 1; k <= nRow; k++)
			{
				printf("%s \t %s\n",resultSet[k * nColumn],resultSet[k * nColumn + 1]);//SQLite好像没有数值概念只存字串
			}
		}

		sqlite3_free_table(resultSet);
		sqlite3_close(db);

}
void selectCallback()//OK
{
		int callback(void *NotUsed, int argc, char **values, char **col_name);
		sqlite3 *db;
		char *msg_error = 0;
		int rc;

		rc = sqlite3_open(DB_FILE, &db);
		if (rc)
		{
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			exit(1);
		}
		rc = sqlite3_exec(db, "select * from student", callback, 0, &msg_error);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", msg_error);
		}
		sqlite3_close(db);

}
int callback(void *NotUsed, int argc, char **values, char **col_name)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", col_name[i], values[i] ? values[i] : "NULL");
	}
	printf("\n");
	return 0;
//	id = 1
//	name = zhaojin
//
//	id = 2
//	name = 李
}



int main(int argc, char **argv)
{
	//linux sqlite2版本中可用 四方向键来操作，而sqlite3就不行了
	createTable();
//	BindInsert();
//	selectData();
//	selectCallback();
//	selectMetaData();
	return 1;
}

}
*/

/*
	drop table student;
	create table student(id varchar(20),name varchar(20));
	insert into student values(10,'张');
*/
