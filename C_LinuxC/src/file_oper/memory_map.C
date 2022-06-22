#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>

#include <unistd.h> //unix standard 出现在其它linux头文件的前面 POSIX其它头文件可能会被影响
#include <sys/mman.h>//memory manipulate
#include <fcntl.h>

namespace memory_map
{
 //内存映射,一块内存可以两个或更多的程序读写
	typedef struct {
		int id;
		char str[24];

	} RECORD;

	#define NRECORDS (100)

	int main(int argc, char *argv[])
	{
		RECORD record, *map;
		int i, f;
		FILE *fp;
		char * filename="/tmp/records.dat";

		fp=fopen(filename, "w+");//返回FILE *
		for (i=0; i<NRECORDS; i++) {
			record.id=i;
			sprintf(record.str, "RECORD%d", i);
			fwrite(&record, sizeof(record), 1, fp);//1表示1个，如数组可多个

		}
		fclose(fp);

		fp=fopen(filename, "r+");
		fseek(fp, 43*sizeof(record), SEEK_SET);
		fread(&record, sizeof(record), 1, fp);
		record.id=143;
		sprintf(record.str, "RECORD%d", record.id);

		fseek(fp, 43*sizeof(record), SEEK_SET);
		fwrite(&record, sizeof(record), 1, fp);
		fclose(fp);

		///使用系统底层API不方便移值,返回文件描述符,fileno(fp)函数根据FILE*返回文件描述符
		f=open(filename, O_RDWR);//O_RDWR读写

		//sys/mman.h文件中 memory manipulate
		//第一个参数addr为NULL自动分配内存，MAP_SHARED修改写入磁盘,PROT_WRITE写权限,PROT=protect
		map=(RECORD*)mmap(NULL, NRECORDS*sizeof(record), PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);
		if(map == MAP_FAILED)
		{
			char * reason=strerror(errno);//errno.h,string.h
			fprintf(stderr,"mmap error! %s\n",reason);
			return -1;
		}
		map[43].id=243;
		sprintf(map[43].str, "RECORD%d", map[43].id);
		msync((void*)map, NRECORDS*sizeof(record), MS_ASYNC);//MS_ASYNC异步写，MS=Memory_Sync
		munmap((void*)map, NRECORDS*sizeof(record));//memory unmap
		close(f);

		exit(0);
	}
}
