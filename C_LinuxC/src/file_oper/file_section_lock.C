#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>


namespace file_lock
{



	#define read_lock(fd, offset, whence, len)  lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
	#define write_lock(fd, offset, whence, len) lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)
	#define err_sys(x) { perror(x); exit(1); }//perror，返回结果同调用 strerror(errno)

	 int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
	 {
			 struct flock    lock;

			 lock.l_type = type;     /* F_RDLCK, F_WRLCK, F_UNLCK */
			 lock.l_start = offset;  /* byte offset, relative to l_whence */
			 lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
			 lock.l_len = len;       /* #bytes (0 means to EOF) 0表示到文件尾 */

			 return( fcntl(fd, cmd, &lock) );
	 }
	 int lock_with_fcntl(int argc, char *argv[]){


		 int             fd, val;
		 pid_t           pid;
		 char            buf[5];
		 struct stat     statbuf;

		 if (argc != 2) {
			 fprintf(stderr, "usage: %s filename\n", argv[0]);
			 exit(1);
		 }
		 if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC )) < 0)
			 err_sys("open error");
		 if (write(fd, "hello world", 11) != 11)
			 err_sys("write error");

		 /* turn on set-group-ID and turn off group-execute */
		 if (fstat(fd, &statbuf) < 0)
			 err_sys("fstat error");
		 if (fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
			 err_sys("fchmod error");

		 sleep(2);//单位秒

		 if ((pid = fork()) < 0) {
			 err_sys("fork error");
		 } else if (pid > 0) {   /* parent */
			 /* write lock entire file */
			 if (write_lock(fd, 0, SEEK_SET, 0) < 0)
				 err_sys("write_lock error");

			 sleep(2);      /* wait for child to set lock and read data */

			 if (waitpid(pid, NULL, 0) < 0)//等子进程
				  err_sys("waitpid error");

		  } else {            /* child */
			  sleep(1);      /* wait for parent to set lock */

			  if ( (val = fcntl(fd, F_GETFL, 0)) < 0)//FL=file flag
					  err_sys("fcntl F_GETFL error");

			  val |= O_NONBLOCK;           /* turn on O_NONBLOCK flag */

			  if (fcntl(fd, F_SETFL, val) < 0)
					  err_sys("fcntl F_SETFL error");

			 /* first let's see what error we get if region is locked */
			 if (read_lock(fd, 0, SEEK_SET, 0) != -1)    /* no wait */
				 err_sys("child: read_lock succeeded");

			 printf("read_lock of already-locked region returns %d: %s\n", errno, strerror(errno));

			 /* now try to read the mandatory locked file */
			 if (lseek(fd, 0, SEEK_SET) == -1)
				 err_sys("lseek error");
			 if (read(fd, buf, 5) < 0)
				 printf("read failed (mandatory locking works)\n");
			 else
				 printf("read OK (no mandatory locking), buf = %5.5s\n", buf);
		  }
		  exit(0);
	  }



	 const char *test_file = "/tmp/test_lock";
	 int lock_with_fcntl_unlock() {
	     int file_desc;
	     struct flock region_to_lock;
	     int res;

	     file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
	     if (!file_desc) {
	         fprintf(stderr, "Unable to open %s for read/write\n", test_file);
	         exit(EXIT_FAILURE);
	     }

	     region_to_lock.l_type = F_RDLCK;
	     region_to_lock.l_whence = SEEK_SET;
	     region_to_lock.l_start = 10;
	     region_to_lock.l_len = 5;
	     printf("Process %d, trying F_RDLCK, region %d to %d\n", getpid(),
	            (int)region_to_lock.l_start, (int)(region_to_lock.l_start + region_to_lock.l_len));
	     res = fcntl(file_desc, F_SETLK, &region_to_lock);
	     if (res == -1) {
	         printf("Process %d - failed to lock region\n", getpid());
	     } else {
	         printf("Process %d - obtained lock region\n", getpid());
	     }

	     region_to_lock.l_type = F_UNLCK;//解锁，其它进程可以？
	     region_to_lock.l_whence = SEEK_SET;
	     region_to_lock.l_start = 10;
	     region_to_lock.l_len = 5;
	     printf("Process %d, trying F_UNLCK, region %d to %d\n", getpid(),
	            (int)region_to_lock.l_start, (int)(region_to_lock.l_start + region_to_lock.l_len));
	     res = fcntl(file_desc, F_SETLK, &region_to_lock);
	     if (res == -1) {
	         printf("Process %d - failed to unlock region\n", getpid());
	     } else {
	         printf("Process %d - unlocked region\n", getpid());
	     }

	     //可第二次解锁
	     region_to_lock.l_type = F_UNLCK;
	     region_to_lock.l_whence = SEEK_SET;
	     region_to_lock.l_start = 0;
	     region_to_lock.l_len = 50;
	     printf("Process %d, trying F_UNLCK, region %d to %d\n", getpid(),
	            (int)region_to_lock.l_start, (int)(region_to_lock.l_start + region_to_lock.l_len));
	     res = fcntl(file_desc, F_SETLK, &region_to_lock);
	     if (res == -1) {
	         printf("Process %d - failed to unlock region\n", getpid());
	     } else {
	         printf("Process %d - unlocked region\n", getpid());
	     }

	     region_to_lock.l_type = F_WRLCK;
	     region_to_lock.l_whence = SEEK_SET;
	     region_to_lock.l_start = 16;
	     region_to_lock.l_len = 5;
	     printf("Process %d, trying F_WRLCK, region %d to %d\n", getpid(),
	            (int)region_to_lock.l_start, (int)(region_to_lock.l_start + region_to_lock.l_len));
	     res = fcntl(file_desc, F_SETLK, &region_to_lock);
	     if (res == -1) {
	         printf("Process %d - failed to lock region\n", getpid());
	     } else {
	         printf("Process %d - obtained lock on region\n", getpid());
	     }

	     region_to_lock.l_type = F_RDLCK;
	     region_to_lock.l_whence = SEEK_SET;
	     region_to_lock.l_start = 40;
	     region_to_lock.l_len = 10;
	     printf("Process %d, trying F_RDLCK, region %d to %d\n", getpid(),
	            (int)region_to_lock.l_start, (int)(region_to_lock.l_start + region_to_lock.l_len));
	     res = fcntl(file_desc, F_SETLK, &region_to_lock);
	     if (res == -1) {
	         printf("Process %d - failed to lock region\n", getpid());
	     } else {
	         printf("Process %d - obtained lock on region\n", getpid());
	     }

	     region_to_lock.l_type = F_WRLCK;
	     region_to_lock.l_whence = SEEK_SET;
	     region_to_lock.l_start = 16;
	     region_to_lock.l_len = 5;
	     printf("Process %d, trying F_WRLCK with wait, region %d to %d\n", getpid(),
	            (int)region_to_lock.l_start, (int)(region_to_lock.l_start + region_to_lock.l_len));
	     res = fcntl(file_desc, F_SETLKW, &region_to_lock);//ＬＫ＝lock wait 一直等下去，但是同一进程，就可以得到
	     if (res == -1) {
	         printf("Process %d - failed to lock region\n", getpid());
	     } else {
	         printf("Process %d - obtained lock on region\n", getpid());
	     }

	     printf("Process %d ending\n", getpid());
	     close(file_desc);
	 }

	 void lock_with_lockf(){
		 int fd;
		 if ((fd = open("/tmp/lockf.txt", O_RDWR | O_CREAT | O_TRUNC )) < 0)
			 	 perror("open error");
		 lseek(fd,10,SEEK_SET);//原因为很早有seek函数，而后来的另一版本返回类型为long,现在已经是off_t
		 //没有fcntl功能多，如读锁，但简单
		 lockf(fd,F_TLOCK,20);//lockf 只能以文件当前位置开始，F_TLOCK先测试于再独占锁，还有F_LOCK独占锁，F_TEST
	 }

	 //文件区域锁(说不能真正防止文件的读写，只是锁的记录方式，要程序去控制)　不能同时使用fcntl(不能使用高级的fwrite,fread因为有缓存,要使用read,write) 和 lockf
	 int main(int argc, char *argv[])
	 {

		 int param_argc=2;
		 char *param_argv[2];
		 param_argv[0]="file_lock";
		 param_argv[1]="/tmp/lock.txt";
		 //lock_with_fcntl(param_argc,param_argv);

		 //lock_with_fcntl_unlock();
		 //F_UNLCK(其它进程可以？)，SETLKW 会一直等下去LK=lock wait

		 lock_with_lockf();
	 }
}


