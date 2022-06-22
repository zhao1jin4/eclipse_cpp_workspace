#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>

#include <sys/resource.h>
#include <sys/time.h>
#include <math.h>

#include <limits.h>
#include <fcntl.h>
namespace lib_log_limit
{

void work()
{
    FILE *f;
    int i;
    double x = 4.5;

    f = tmpfile();
    for(i = 0; i < 10000; i++) {
        fprintf(f,"Do some output\n");
        if(ferror(f)) {
            fprintf(stderr,"Error writing to temporary file\n");
            exit(1);
        }
    }
    for(i = 0; i < 1000000; i++)
        x = log(x*x + 3.21);//math.h
}

extern int errno;
int the_limit()
{
	int int_max=INT_MAX; //<limits.h>
	int filename_max=NAME_MAX;//可能是特定系统的
	int filename_max2=pathconf("/tmp",_PC_NAME_MAX);
	int filename_max3=fpathconf(open("/tmp",O_RDONLY),_PC_NAME_MAX);// 参数是文件描述符

    struct rusage r_usage;
    struct rlimit r_limit;
    int priority;
    work();
    getrusage(RUSAGE_SELF, &r_usage);//r=resource,除了 RUSAGE_SELF　还有 RUSAGE_CHILDREN
    printf("CPU usage: User = %ld.%06ld, System = %ld.%06ld\n",
        r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec,
        r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);


    //优先级范围-20到19,-20最高,19最低(nice,renice命令ps -el 有PRI列)，getpriority返回错误的-1重合,要使用errno判断才行
    priority = getpriority(PRIO_PROCESS, getpid());//还有　PRIO_PGRP 进程组,　PRIO_USER
    printf("Current priority = %d\n", priority);

    getrlimit(RLIMIT_FSIZE, &r_limit);//FSIZE=file size ,还有RLIMIT_NOFILE 打开文件数
    printf("Current FSIZE limit: soft = %ld, hard = %ld\n",
        r_limit.rlim_cur, r_limit.rlim_max);

    r_limit.rlim_cur = 2048;//软限制
    r_limit.rlim_max = 4096;//硬限制，可用ulimit命令
    printf("Setting a 2K file size limit\n");
    setrlimit(RLIMIT_FSIZE, &r_limit);
    work();
}

	int the_sys_log()
	{
		FILE *f;
		f = fopen("not_here","r");
		if(!f)
			//默认写到/var/log/messages文件中， /etc/rsyslog.conf中有配置*.info  /var/log/messages
			syslog(LOG_ERR|LOG_USER,"oops - %m\n");//<syslog.h> ,%m 是errno转换后的消息，即　strerror(errno)
			//在调用syslog前可不调用openlog
		int logmask;
		//第一个参数是每个日志的前缀，区分哪个程序，LOG_CONS,如果写日志失败如磁盘满，就发送到控制台
		openlog("logmask", LOG_PID|LOG_CONS, LOG_USER);
		syslog(LOG_INFO,"informative message, pid = %d", getpid());//也有getppid();
		syslog(LOG_DEBUG,"debug message, should appear");//不显示，因/var/log/messages配置info
		logmask = setlogmask(LOG_UPTO(LOG_NOTICE));//LOG_UPTO;只记录>指定日志级别,LOG_NOTICE来记录，LOG_INFO就没有了
		syslog(LOG_NOTICE,"notice, record in file");//记录
		syslog(LOG_INFO,"info, should not appear");//不记录

		logmask = setlogmask(LOG_MASK(LOG_NOTICE));//也有LOG_MASK();只记录指定一个日志级别
		syslog(LOG_NOTICE,"notice, record in file");//记录
		syslog(LOG_WARNING,"WARNING, should not appear");//不记录
	}

	int main (int argc, char *argv[])
	{
		//the_sys_log();
		the_limit();
		return 0;
	}

};



