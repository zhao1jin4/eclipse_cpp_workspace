#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <limits.h>



namespace file_bad
{
//linux底层 文件操作API ，不能移植，建议用stdio.h的标准的


int my_write_file()
{
  int fd = -1,i;
  size_t size = -1;
  int input = 0;
  /*存放数据的缓冲区*/
  char buf[]="quick brown fox jumps over the lazy dog";
  char filename[] = "/tmp/test.txt";

  /*打开文件，如果文件不存在，则报错*/
	fd = open(filename,O_RDWR|O_TRUNC);
	if(-1 == fd){
		/*文件已经存在*/
	  printf("Open file %s failure,fd:%d\n",filename,fd);
	}	else	{
		/*文件不存在，创建并打开*/
	  printf("Open file %s success,fd:%d\n",filename,fd);
	}

	/*将数据写入到文件test.txt中*/
	size = write(fd, buf,strlen(buf));
	printf("write %d bytes to file %s\n",size,filename);

	fsync(fd);//写到设备里去

	/*关闭文件*/
	close(fd);

	return 0;
}
int my_read_file(){
	int fd = -1,i;
	  ssize_t size = -1;
	  /*存放数据的缓冲区*/
	  char buf[10];
	  char filename[] = "/tmp/test.txt";
	  /*打开文件，如果文件不存在，则报错*/
		fd = open(filename,O_RDONLY);
		if(-1 == fd){
			/*文件已经存在*/
		  printf("Open file %s failure,fd:%d\n",filename,fd);
		}	else	{
			/*文件不存在，创建并打开*/
		  printf("Open file %s success,fd:%d\n",filename,fd);
		}

		/*循环读取数据，直到文件末尾或者出错*/
		while(size){
			/*每次读取10个字节数据*/
			size = read(fd, buf,10);
			if( -1 == size)	{
				/*读取数据出错*/
				close(fd);/*关闭文件*/
				printf("read file error occurs\n");
				/*返回*/
				return -1;
			}else{
				/*读取数据成功*/
				if(size >0 ){
					/*获得size个字节数据*/
					printf("read %d bytes:",size);
					/*打印引号*/
					printf("\"");
					/*将读取的数据打印出来*/
					for(i = 0;i<size;i++){
						printf("%c",*(buf+i));
					}
					/*打印引号并换行*/
					printf("\"\n");
				}else{
					printf("reach the end of file\n");
				}
			}
		}

}

int seek_write()
{
  int fd = -1,i;
  ssize_t size = -1;
  off_t offset = -1;
  /*存放数据的缓冲区*/
  char buf1[]="01234567";
  char buf2[]="ABCDEFGH";
  /*文件名*/
  char filename[] = "/tmp/hole.txt";
  int len = 8;

  /*创建文件hole.txt*/
	fd = open(filename,O_RDWR|O_CREAT|O_EXCL,//O_EXCL(全称是exclusive) 和 O_CREAT一起用， 如文件存在，就失败
			S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP); //这里的权限是和umask命令相结合的，如umask为0022组的写权限被禁止，这里给了也不行
	if(-1 == fd){
		/*创建文件失败*/
	  return -1;
	}

	/*将buf1中的数据写入到文件Hole.txt中*/
	size = write(fd, buf1,len);
	if(size != len){
		/*写入数据失败*/
		return -1;
	}

	/*设置文件偏移量为绝对值的32*/
	offset = lseek(fd, 32, SEEK_SET);//还有 SEEK_CUR 相对当前位置
	if(-1 == offset){
		/*设置失败*/
		return -1;
	}
	/*将buf2中的数据写入到文件hole.txt中*/
	size = write(fd, buf2,len);
	if(size != len){
		/*写入数据失败*/
		return -1;
	}

	/*关闭文件*/
	close(fd);

	return 0;
}
int main(int argc, char *argv[]){
//		my_write_file();
//		my_read_file();
		seek_write();
}


};
