
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>


namespace  lib_inet_xxx{
void my_sockopt_testing(){
	int sock;
	//setsockopt(sock,SOL_SOCKET);//socket极别的设置,SOL=socket option L??

	protoent * p=getprotobyname("TCP");
	//TCP/UDP 极别的设置
	setsockopt(sock, p->p_proto ,SO_KEEPALIVE,(const void *)1,(socklen_t)sizeof(int));//SO=socket option
	//SO_KEEPALIVE 和 SO_DEBUG 是开关, 设置值为0或1

	linger lin; // linger 逗留，缓慢消失
	lin.l_linger= //time
	lin.l_onoff=1;
	setsockopt(sock, p->p_proto ,SO_LINGER,(const void *)&lin,(socklen_t)sizeof(lin));//socket 关闭之前拖延时间

}
void lib_inet_xxx(){

	struct in_addr ip,local,network;
	char addr1[]="192.168.1.1";		/* 网络地址字符串 */
	char addr2[]="255.255.255.255";
	char addr3[]="192.16.1";
	char addr[16];
	char *str=NULL,*str2=NULL;


	int err = 0;

	err = inet_aton(addr1, &ip);//把字串的IP地址转换为in_addr类型参数输出, aton=ascii to net
	if(err){
		printf("inet_aton:string %s value is:0x%x\n",addr1, ip.s_addr);
	}else{
		printf("inet_aton:string %s  error\n",addr1);
	}

	/* inet_addr，先测试192.168.1.1，在测试255.255.255.255 */
	ip.s_addr = inet_addr(addr1);//把字串的IP地址转换为in_addr_t返回(网络字节序)
	//返回值如为-1错误和255.255.255.255表示的值冲突的


	//inet_network(addr1);//把字串的IP地址转换为in_addr_t返回,.h文件中和书上说网络字节序,和inet_addr()不是一样吗??(man 说是主机节序??)

	if(err != -1){
		printf("inet_addr:string %s value is:0x%x\n",addr1, ip.s_addr);
	}else{
		printf("inet_addr:string %s  error\n",addr1);
	};
	ip.s_addr = inet_addr(addr2);
	if(ip.s_addr != -1){
		printf("inet_addr:string %s value is:0x%x\n",addr2, ip.s_addr);
	}else{
		printf("inet_addr:string %s  error\n",addr2);
	};

	/* inet_ntoa，先测试192.168.1.1，在测试255.255.255.255
	*	证明函数的不可重入性
	 */
	ip.s_addr = 192<<24|168<<16|1<<8|1;
	str = inet_ntoa(ip);//把in_addr类型转换为类字串的IP地址返回,ntoa=net to ascii
	ip.s_addr = 255<<24|255<<16|255<<8|255;
	str2 = inet_ntoa(ip);
	printf("inet_ntoa:ip:0x%x string1 %s,pre is:%s \n",ip.s_addr,str2,str);

	/* 测试函数inet_addr */
	ip.s_addr = inet_addr(addr3);
	if(err != -1){
		printf("inet_addr:string %s value is:0x%x\n",addr3, ip.s_addr);
	}else{
		printf("inet_addr:string %s  error\n",addr3);
	};
	str = inet_ntoa(ip);
	printf("inet_ntoa:string %s ip:0x%x \n",str,ip.s_addr);

	/* 测试函数inet_lnaof，获得本机地址 */
	inet_aton(addr1, &ip);
	local.s_addr = htonl(ip.s_addr);
	local.s_addr = inet_lnaof(ip);//返回IP地址中的主机部分in_addr_t类型, lnaof=local network address of

	str = inet_ntoa(local);
	printf("inet_lnaof:string %s ip:0x%x \n",str,local.s_addr);

	/* 测试函数inet_netof，获得本机地址 */
	network.s_addr = inet_netof(ip);//得到网络部分,netof=net of
	printf("inet_netof:value:0x%x \n",network.s_addr);


	in_addr_t net=0x7F;//如0开头是8进制
	in_addr_t host=0x1;
	in_addr res_ip=inet_makeaddr(net,host);//网段+主机
	char* str_ip=inet_ntoa(res_ip);//127.0.0.1
	printf("网段+主机 IP=%s\n",str_ip);



}
int main(int argc, char *argv[])
{
	//my_sockopt_testing();/未测试
	lib_inet_xxx();
}

}
