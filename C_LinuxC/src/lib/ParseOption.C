#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
//#include <unistd.h>


namespace myoption
{


	char *oci_username = NULL;
	char *oci_password = NULL;
	char *oci_sid = NULL;



	void parseOption1(int argc, char* argv[])
	{
		// -u scott -p tigger -s xe
		int opt;
		while ((opt = getopt(argc, argv, "u:p:s:h")) != -1)//-1 表示结束，后有:表示有值，如未传值optarg为：
		{
			switch (opt)
			{
			case 'u':
				oci_username = optarg; //optarg　是值
				break;
			case 'p':
				oci_password = optarg; //optarg
				break;
			case 's':
				oci_sid = optarg; //optarg
				break;
			case 'h':
				printf("usage:\n");
				printf("\t1.\t SynDB -u <oracle_username> -p <oracle_password> -s <oracle_sid>\n");
				printf("example:\n");
				printf("\t1.\t SynDB -u scott -p tiger -s orcl\n\n");
				exit(1);
			case '?'://未知选项
				printf("unknow option:%c\n", optopt);//optopt　未知选项的值

				printf("usage:\n");
				printf("\t1.\t SynDB -u <oracle_username> -p <oracle_password> -s <oracle_sid>\n");
				printf("example:\n");
				printf("\t1.\t SynDB -u scott -p tiger -s orcl\n\n");
				exit(1);
			}
			printf("%d", optind);//optind　索引
		}
		//其它参数
		for (; optind < argc; optind++)
			printf("--%s\n", argv[optind]);

		printf("u=%s\n", oci_username);
		printf("p=%s\n", oci_password);
		printf("s=%s\n", oci_sid);

	}
	void parseOption2(int argc, char* argv[])
	{
		// -u scott -p tiger -s xe
		//--oracle-username hr --oracle-password hrpwd --oracle-sid orcl

		if (argc < 2)
		{
			printf("usage:\n");
			printf("\t1.\t SynDB -u <oracle_username> -p <oracle password> -s <oracle sid>\n");
			printf("\t2.\t SynDB --oracle-username <oracle username>  --oracle-password  <oracle password>  --oracle_sid <oracle sid>\n");

			printf("example:\n");
			printf("\t1.\t SynDB -u scott -p tiger -s orcl\n");
			printf("\t1.\t SynDB --oracle-username scott --oracle-password tiger --oracle-sid orcl\n");
			exit(1);
		}
		struct option longopts[] = {
				//长名，是否有参数２表示可选
				{ "oracle-username", 1, NULL, 'u' },
				{ "oracle-password", 1, NULL, 'p' },
				{ "oracle-sid", 1, NULL, 's' },
				{ "help", 0, NULL, 'h' },
				{ 0, 0, 0, 0 } //必须要有
		};
		int option_index = 0;
		int opt;
		while ((opt = getopt_long(argc, argv, "u:p:s:h", longopts, &option_index)) != -1)
		{
			switch (opt)
			{
			case 'u':
				oci_username = optarg;
				break;
			case 'p':
				oci_password = optarg;
				break;
			case 's':
				oci_sid = optarg;
				break;
			case 'h':
				//--oracle-username scott --oracle-password tigger --oracle-sid xe
				printf("usage:\n");
				printf("\t1.\t SynDB -u <oracle username> -p <oracle password> -s <oracle sid>\n");
				printf("\t2.\t SynDB --oracle-username <oracle username>  --oracle-password  <oracle password>  --oracle-sid <oracle-sid>\n");

				printf("example:\n");
				printf("\t1.\t SynDB -u scott -p tiger -s orcl\n");
				printf("\t1.\t SynDB --oracle-username scott --oracle-password tiger --oracle-sid orcl\n");
				exit(1);
			case '?':
				printf("unknow option:%c\n", optopt);//optopt
				printf("usage:\n");
				printf("\t1.\t SynDB -u <oracle_username> -p <oracle password> -s <oracle sid>\n");
				printf("\t2.\t SynDB --oracle-username <oracle username>  --oracle-password  <oracle password>  --oracle_sid <oracle sid>\n");

				printf("example:\n");
				printf("\t1.\t SynDB -u scott -p tiger -s orcl\n");
				printf("\t1.\t SynDB --oracle-username scott --oracle-password tiger --oracle-sid orcl\n");
				exit(1);
			}
			//printf("option %s", longopts[option_index].name);
		}

	}
	int main(int argc, char* argv[])
	{
		//parseOption1(argc,argv);
		parseOption2(argc, argv);
		return 1;
	}
}
