#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string.h>
#include <errno.h>

#include <pwd.h>
#include <sys/utsname.h>//uts=UNIX Time Sharing, UNIX分时操作系统

namespace lib_cmd
{

	int userinfo()
	{
		uid_t uid;
		gid_t gid;
		struct passwd *pw;
		uid = getuid();
		gid = getgid();
		printf("User is %s\n", getlogin());
		printf("User IDs: uid=%d, gid=%d\n", uid, gid);
		pw = getpwuid(uid);//<pwd.h>
		printf("UID passwd entry:\n name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
		pw = getpwnam("root");
		printf("root passwd entry:\n");
		printf("name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
	}
	void my_userinfo(){
		setpwent();//重定位到开头
		while(true){
			passwd * pw=getpwent();//ent=entry
			printf("name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
					pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
			if(pw->pw_uid== getuid()){
				printf("found myself\n");
				endpwent();//终止处理
				break;
			}
		}
		setuid(getuid());//对当前进程修改uid,getuid是真实的
		geteuid();//e=effective

	}

	void pc_info(){
		uid_t uid=getuid();
		char * loiginUser=getlogin();
		printf("loiginUser=%s,uid=%d \n",loiginUser,uid);

		char computer[256];
		struct utsname uts;
		if(gethostname(computer, 255) != 0 || uname(&uts) < 0) {//uname(同命令unix name)在sys/utsname.h
			fprintf(stderr, "Could not get host information\n");
			exit(1);
		}
		printf("Computer host name is %s\n", computer);
		printf("System is %s on %s hardware\n", uts.sysname, uts.machine);//Linux on x86_64
		printf("Nodename is %s\n", uts.nodename);
		printf("Version is %s, %s\n", uts.release, uts.version);//kernel version
	}
	void print_error(int error_code){
		if(error_code == -1){
		   char * reason=strerror(errno);//errno.h,string.h
		   fprintf(stderr,"error! %s\n",reason);
		   exit(0);
		}
	}
	void fs_cmd(){
		char * file="/tmp/test.txt";//必须是已经存在的
		int res=chmod(file,S_IRUSR|S_IWUSR|S_IRGRP);//mode同open
		print_error(res);

		res=chown(file,getuid(),getgid());
		print_error(res);

		res=link(file,"/tmp/link_test.txt");//是一个硬链接
		print_error(res);

		res=unlink("/tmp/link_test.txt");
		print_error(res);

		res=symlink(file,"/tmp/symlink_test.txt");//软链接
		print_error(res);

		res=unlink("/tmp/symlink_test.txt");
		print_error(res);

		res=mkdir("/tmp/empty_dir",S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);//<sys/stat.h>
		print_error(res);

		res=chdir("/tmp/empty_dir");//cd 命令
		print_error(res);

		char current_idr[1024];
		getcwd(current_idr,sizeof(current_idr));//pwd命令，cwd=current work dir
		printf("current dir is =%s\n",current_idr);

		res=rmdir("/tmp/empty_dir");
		print_error(res);

	}
	int main (int argc, char *argv[])
	{
		//fs_cmd();
		pc_info();
		userinfo();
		my_userinfo();
		return 0;
	}

};



