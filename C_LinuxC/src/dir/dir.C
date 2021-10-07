
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#include <dirent.h>

namespace dir
{

	void printdir(char * dir ,int depth)
	{
        DIR *dp;
        struct dirent * entry;
        struct stat statbuf;
        if(( dp=opendir(dir))==NULL)
        {
                fprintf(stderr,"cann't open ");
                return;
        }
        chdir (dir);
        while((entry=readdir(dp))!=NULL)
        {
                lstat(entry->d_name,&statbuf);
                if(S_ISDIR(statbuf.st_mode))
                {
                        if(strcmp(".",entry->d_name)==0|| strcmp("..",entry->d_name)==0)
                                continue;

                        printf("%*s%s/\n",depth,"|",entry->d_name);//""
                        printdir(entry->d_name,depth+4);
                }
                else
                printf("%*s%s\n",depth,"|",entry->d_name);
        }
        chdir("..");
        closedir(dp);
}

	int main(int argc, char *argv[])
	{
		printf("%-10d\n",101010);
		printf("%-*s", 10, "abc");// 表示输出字符串左对齐输出10，如果字符串不够20个，以空格补齐
		printdir("/tmp",0);// /tmp  ,C:/temp
		exit(0);
	}
}
