#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
namespace mysql_c_crud
{

void my_ddl(MYSQL * my_connection,char * sql)
{
	int res = mysql_query(my_connection, sql);
	  if (!res) {
		 printf("DDL  %lu rows\n", (unsigned long)mysql_affected_rows(my_connection));
	  } else {
		 fprintf(stderr, "DDL error %d: %s\n", mysql_errno(my_connection),
											  mysql_error(my_connection));
	  }
}
void my_query_each(MYSQL * my_connection,char * sql){
	int res = mysql_query(my_connection, sql);
	  if (res) {
		 printf("SELECT error: %s\n", mysql_error(my_connection));
	  } else {
		   MYSQL_RES *res_ptr= mysql_use_result(my_connection);//一次返回一行结果用mysql_use_result
		   //就不能和mysql_data_seek,mysql_row_seek,mysql_row_tell一起使用了
		 if (res_ptr) {
			 MYSQL_ROW sqlrow;
			while ((sqlrow = mysql_fetch_row(res_ptr))) {
			   unsigned int field_count = 0;
			   while (field_count < mysql_field_count(my_connection)) {
			        printf("%s ", sqlrow[field_count]);
			        field_count++;
			   }
			   printf("\n");

			}
			mysql_free_result(res_ptr);
		 }
	  }
}
void my_display_header(MYSQL_RES * res_ptr) {
   MYSQL_FIELD *field_ptr;
   printf("Column details:\n");
   while ((field_ptr = mysql_fetch_field(res_ptr)) != NULL) {
      printf("\t Name: %s\n", field_ptr->name);
      printf("\t Type: ");
      if (IS_NUM(field_ptr->type)) {
         printf("Numeric field\n");
      } else {
         switch(field_ptr->type) {
            case FIELD_TYPE_VAR_STRING:
               printf("VARCHAR\n");
            break;
            case FIELD_TYPE_LONG:
               printf("LONG\n");
            break;
            default:
              printf("Type is %d, check in mysql_com.h\n", field_ptr->type);
         }
      }
      printf("\t Max width %ld\n", field_ptr->length);
      if (field_ptr->flags & AUTO_INCREMENT_FLAG)
         printf("\t Auto increments\n");
      printf("\n");
   }
}
void my_query_all_header(MYSQL * my_connection,char * sql){
	int res = mysql_query(my_connection, sql);
	  if (res) {
		 fprintf(stderr, "SELECT error: %s\n", mysql_error(my_connection));
	  } else {
		  MYSQL_RES * res_ptr = mysql_store_result(my_connection);//mysql_store_result 一次查所有记录
		 if (res_ptr) {
			my_display_header(res_ptr);
			MYSQL_ROW sqlrow;
			while ((sqlrow = mysql_fetch_row(res_ptr))) {
				 unsigned int field_count  = 0;
				   while (field_count < mysql_field_count(my_connection)) {
					  if (sqlrow[field_count])
						  printf("%s ", sqlrow[field_count]);
					  else
						  printf("NULL");
					  field_count++;
				   }
				   printf("\n");
			}
			if (mysql_errno(my_connection)) {
			 fprintf(stderr, "Retrive error: %s\n",
								mysql_error(my_connection));
			}
		 }
		 mysql_free_result(res_ptr);
	  }
}


void my_transaction_cn(MYSQL * my_connection){
	  printf("character set =%s\n",mysql_character_set_name(my_connection));
	  if (!mysql_set_character_set(my_connection, "utf8"))
	  {
	      printf("New client character set: %s\n",
	             mysql_character_set_name(my_connection));
	  }
	 mysql_autocommit(my_connection, 0);
	 my_ddl(my_connection,"INSERT INTO children(fname, age) VALUES('li',1)"); //因SQL是char*所不支持中文？
	 mysql_rollback(my_connection);
	 my_ddl(my_connection,"INSERT INTO children(fname, age) VALUES('wang', 2)");
	 mysql_commit(my_connection);
}

int main(int argc, char *argv[]) {
   MYSQL *conn_ptr;
   conn_ptr = mysql_init(NULL);//如果参数是NULL返回新的
   if (!conn_ptr) {
      fprintf(stderr, "mysql_init failed\n");
      return EXIT_FAILURE;
   }
   unsigned int timeout=7;
    mysql_options(conn_ptr,MYSQL_OPT_CONNECT_TIMEOUT,(const char * )&timeout); //连接超时时间
    mysql_options(conn_ptr,MYSQL_SET_CHARSET_NAME,"utf8");

    //报  Plugin caching_sha2_password could not be loaded:  的解决方式
    //ALTER USER zh@'%' IDENTIFIED WITH mysql_native_password   BY '123';
	char *host="127.0.0.1",*user = "zh", *pwd = "123", *dbname = "mydb";
	unsigned int port=3306;
    //char * sock="/tmp/mysql.sock"; //如果host值为localhost就会使用sock连接
    char * sock=NULL;

    MYSQL* conn_res = mysql_real_connect(conn_ptr, host, user, pwd,
    		dbname, port, sock, 0);
   if (conn_res) {
      printf("Connection success\n");
   } else {
      printf("Connection failed\n");
      if (mysql_errno(conn_ptr)) {
		   fprintf(stderr, "Connection error %d: %s\n", mysql_errno(conn_ptr), mysql_error(conn_ptr));
	   }
   }

   my_ddl(conn_ptr," drop tables if exists children;");

   	char * create_sql="CREATE TABLE children (\
   	   childno int(11)  NOT NULL auto_increment,\
   	   fname varchar(30),\
   	   age int(11),\
   	   PRIMARY KEY (childno)\
   	)ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;";
   my_ddl(conn_ptr,create_sql);

   my_ddl(conn_ptr,"INSERT INTO children(fname, age) VALUES('Ann', 3)");

   my_query_each(conn_ptr, "SELECT LAST_INSERT_ID()");
   my_query_all_header(conn_ptr, "SELECT childno, fname, age FROM children WHERE age > 2");
   my_transaction_cn(conn_ptr);//不支持中文？查询也不行
   //SQL没有动态绑定参数

   mysql_close(conn_ptr);
   return EXIT_SUCCESS;
}


}

