#include "main.h"

#include <stdlib.h>
#include <stdio.h>


//	const int *A ��  int const *A; //const����ָ��Ķ���A�ɱ䣬Aָ��Ķ��󲻿ɱ�
//	int *const A;            //const����ָ��A��     A���ɱ䣬Aָ��Ķ���ɱ�
//	const int *const A;      //ָ��A��Aָ��Ķ��󶼲��ɱ�
int main (int  argc, char* argv[])
{
	setbuf(stdout, NULL);//CDT ���߱������������������������̨,ȫ�ֵ�
	//fflush(stdout);//CDT ���߱������������������������̨���ֲ���

	  openssl::main(argc, argv);//���lib����

	  //sqlite3 ,win64����lib������ĿǰӰ������
//	  sqlite::main(argc, argv);

	  //mysql ,win64����lib������ĿǰӰ������
//	  mysql_c::main(argc, argv);
//	  mysql_c_crud::main(argc, argv);//��֧�����ģ�

//	  mysql8_cpp::main(argc, argv);//��
//	  mongoDB::main(argc, argv);//not work???



	return 1;

}
