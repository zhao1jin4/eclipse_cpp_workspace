
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>

namespace  lib_get_etc_name{

int main(int argc, char *argv[])
{
    char *host, **names, **addrs;
    struct hostent *hostinfo; //<netdb.h>

/*  Set the host in question to the argument supplied with the getname call,
    or default to the user's machine.  */

    if(argc == 1) {
        char myname[256];
        gethostname(myname, 255);
        host = myname;
    }
    else
        host = argv[1];

/*  Make the call to gethostbyname and report an error if no information is found.  */

    //读/etc/hosts文件,还有byaddr
    hostinfo = gethostbyname(host);
    if(!hostinfo) {
        fprintf(stderr, "cannot get info for host: %s\n", host);
        exit(1);
    }

/*  Display the hostname and any aliases it may have.  */

    printf("results for host %s:\n", host);
    printf("Name: %s\n", hostinfo -> h_name);
    printf("Aliases:");
    names = hostinfo -> h_aliases;
    while(*names) {
        printf(" %s", *names);
        names++;
    }
    printf("\n");

/*  Warn and exit if the host in question isn't an IP host.  */

    if(hostinfo -> h_addrtype != AF_INET) {
        fprintf(stderr, "not an IP host!\n");
        exit(1);
    }

/*  Otherwise, display the IP address(es).  */

    addrs = hostinfo -> h_addr_list;
    while(*addrs) {
        printf(" %s", inet_ntoa(*(struct in_addr *)*addrs));//inet_ntoa 把in_addr转换为IPV4以点分隔的字串
        addrs++;
    }
    printf("\n");


    struct servent * servinfo= getservbyname("ssh","tcp");//读/etc/services
    if(!servinfo) {
          fprintf(stderr, "cannot get info for services: daytime\n");
          exit(1);
      }
    printf("ssh tcp port : %d",ntohs(servinfo->s_port));
    exit(0);
}

}
