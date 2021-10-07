#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

namespace memory
{


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

		fp=fopen(filename, "w+");
		for (i=0; i<NRECORDS; i++) {
			record.id=i;
			sprintf(record.str, "RECORD%d", i);
			fwrite(&record, sizeof(record), 1, fp);

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

		f=open("redcords.dat", O_RDWR);
		map=(RECORD*)mmap(0, NRECORDS*sizeof(record), PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);

		map[43].id=243;
		sprintf(map[43].str, "RECORD%d", map[43].id);
		msync((void*)map, NRECORDS*sizeof(record), MS_ASYNC);
		munmap((void*)map, NRECORDS*sizeof(record));
		close(f);

		exit(0);
	}
}
