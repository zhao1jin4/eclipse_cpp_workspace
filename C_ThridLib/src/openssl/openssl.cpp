#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>
#include <openssl/md5.h>
#include <openssl/des.h>
#include<openssl/dh.h>

// -l crypto
namespace openssl
{
	void sha1(){
		SHA_CTX ctx;
		SHA1_Init(&ctx);//��������״̬��

		const char * str="����ԭʼ����";
		size_t len=strlen(str);
		SHA1_Update(&ctx,str,len);//��������״̬��
		//�ɶ��udpate
		const char * str1="���ǵڶ�������";
		size_t len1=strlen(str1);
		SHA1_Update(&ctx,str1,len1);

		unsigned char * res=new unsigned char[SHA_DIGEST_LENGTH];

		SHA1_Final(res,&ctx);//��������״̬��

		//���ת��
		char * hexRes=new char[SHA_DIGEST_LENGTH *2 +1];
		for(int i=0;i<SHA_DIGEST_LENGTH;i++){
			sprintf(&hexRes[i*2],"%02x",res[i]);
		}
		printf("SHA1 ���Ϊ=%s\n",hexRes);

	}
	void sha256(){
		const  char * str="����ԭʼ����";
		size_t len=strlen(str);
		unsigned char * res=new unsigned char[SHA256_DIGEST_LENGTH];
		//ֻ�ɷ�һ������
		SHA256((const unsigned char *)str,len,res);//����ָ������ָ��,ǿת����ı�����

		//���ת��
		char * hexRes=new char[SHA256_DIGEST_LENGTH *2 +1];
		for(int i=0;i<SHA256_DIGEST_LENGTH;i++){
			sprintf(&hexRes[i*2],"%02x",res[i]);
		}
		printf("SHA256 ���Ϊ=%s\n",hexRes);
	}
	void md5(){
		const  char * str="����ԭʼ����";
		size_t len=strlen(str);
		unsigned char * res=new unsigned char[MD5_DIGEST_LENGTH];

		MD5((const unsigned char *)str,len,res);//ǿת����ı�����

		//���ת��
		char * hexRes=new char[MD5_DIGEST_LENGTH *2 +1];
		for(int i=0;i<MD5_DIGEST_LENGTH;i++){
			sprintf(&hexRes[i*2],"%02x",res[i]);
		}
		printf("MD5 ���Ϊ=%s\n",hexRes);
	}

	/*��������ģʽ
	 * 1.ECB(�������)
	 * 2.CBC (���ã���Ҫ��һ����ʼ������)
	 * 3.CFB (Ҫһ����ʼ������)
	 * 4.OFB (Ҫһ����ʼ������)
	 * 5.CTR
	*/
	int des_ncbc(){
		 char *keystring = "this is my key";
		  DES_cblock key;
		  DES_key_schedule key_schedule;

		  //����һ�� key
		  DES_string_to_key(keystring, &key);
		  if (DES_set_key_checked(&key, &key_schedule) != 0) {
			  printf("convert to key_schedule failed.\n");
			  return -1;
		  }

		  //��Ҫ���ܵ��ַ���
		  unsigned char input[] = "this is a text being encrypted by openssl";
		  size_t len = (sizeof(input)+7)/8 * 8;// +7 ��ʾ����ʧԭ�������ݣ������ͷ��鳤��ͬ����8�� �� ��8��8����˼8��������

		  void  *outputTmp = malloc(len+1);
		  unsigned char *output =(unsigned char *)outputTmp;
		  //IV
		  DES_cblock ivec;//��������Ϊ8

		  //IV����Ϊ0x0000000000000000
		  memset((char*)&ivec, 0, sizeof(ivec));

		  //����
		  DES_ncbc_encrypt(input, output, sizeof(input), &key_schedule, &ivec, DES_ENCRYPT);//ͷ�ļ�ע��˵�� ���DES_cbc_encrypt

		  //��������Ժ������
		  printf("enc: ");
		  for (int i = 0; i < len; ++i)
			 printf("%02x", output[i]);
		  printf("\n");

		  memset((char*)&ivec, 0, sizeof(ivec));

		  //����
		  DES_ncbc_encrypt(output, input, len, &key_schedule, &ivec, 0);

		  printf("dec : %s\n", input);

		  free(output);
	}




	void print_bigdata(const BIGNUM *b, char *title) {
		unsigned char a[2048] = {0};
		int len = BN_bn2bin(b, a);//bn=bignum
		int i = 0, c = 0;
		printf("===================================== %s =====================================\n", title);
		for (; i<len; i++) {
			printf("0x%02x ", a[i]);
			c++;
			if (!(c%16))
				printf("\n");
		}
		printf("\n");
	}

	void print_hexdata(unsigned char *b, int len, char *title) {
		int i = 0, c = 0;
		printf("===================================== %s =====================================\n", title);
		for (; i<len; i++) {
			printf("0x%02x ", b[i]);
			c++;
			if (!(c%16))
				printf("\n");
		}
		printf("\n");
	}

	/*

	https://blog.csdn.net/lanzhihui_10086/article/details/118864865
	����ʵ���е��κ�һ��ʹ���Լ���˽Կ����һʵ��Ĺ�Կ���õ�һ���Գ���Կ����һ�Գ���Կ����ʵ�嶼���㲻������

	�ͷ��ͽ��շ�������ͬ�Ĵ�����n��g�������������Ǳ��ܵ�
	���ͷ�ѡ��һ�����������x������X= g^x mod n ������X�������ߣ�
	���շ�ѡ��һ�����������y������Y = g^y mod n ������Y�����ͷ���
	˫��������Կ�����ͷ���ԿΪk1=Y^x mod n�����շ���ԿΪk2=X^y mod n��
	����k1=k2=g^(xy) mod n��

	DH ������ʼ����������ĸ
	˫������֪��������(����������Ҳû��ϵ)��˫���������ɴ���������������һ�����㣬���͸��Է�������ʱҪ��ֹα�죬����������Ҳû��ϵ������֪�����㹫ʽ�������յ���˫���ټ��㶼�ɵõ�һ����ͬ��ֵ
 	DH��Կ������Ҫ1024λ�����ܱ�֤���㹻���С����ڰ�ȫ��

	 */
	int dh_main()//p,g��ʼ���õ�
	{
		int key_bits = 768;
		int ret;
		// ����DH���ݽṹ
		DH *d1 = NULL;
		d1=DH_new();
		// ����d��Կ����������Կ�����ǿ��Թ�����
		ret=DH_generate_parameters_ex(d1,key_bits,DH_GENERATOR_2,NULL);
		if(ret!=1)
		{
			printf("DH_generate_parameters_ex err!\n");
			return -1;
		}
		ret=DH_generate_key(d1);
		if(ret!=1)
		{
			printf("DH_generate_key err!\n");
			return -1;
		}

		// ��ȡd1��p,g,pub_key,pri_key
		const BIGNUM *d1p = NULL, *d1g = NULL;
		DH_get0_pqg(d1, &d1p, NULL, &d1g);
		const BIGNUM *d1pub_key = NULL, *d1priv_key = NULL;
		DH_get0_key(d1, &d1pub_key, &d1priv_key);

//		print_bigdata(d1p,"d1p");
//		print_bigdata(d1pub_key,"d1pub_key");
//		print_bigdata(d1priv_key,"d1priv_key");

		//----��һ��
		// ����DH���ݽṹ
		DH *d2 = NULL;
		d2=DH_new();

		// p �� g Ϊ��������Կ��������˿��Կ���,ͨ��p,g�������Թ���d2
		BIGNUM *t_p = NULL, *t_g = NULL;
		t_p=BN_dup(d1p);//����
		t_g=BN_dup(d1g);
		DH_set0_pqg(d2, t_p, NULL, t_g);
		// ���ɹ�˽Կ,���ڲ������ɹ�����Կ
		ret=DH_generate_key(d2);
		if(ret!=1)
		{
			printf("DH_generate_key err!\n");
			return -1;
		}


		// ��ȡd2��p,g,pub_key,pri_key
//��ǰ���Ѿ�DH_set0_pqg���ﲻ����DH_get0_pqg
//		const BIGNUM *d2p = NULL, *d2g = NULL;
//		DH_get0_pqg(d2, &d2p, NULL, &d2g);

		const BIGNUM *d2pub_key = NULL, *d2priv_key = NULL;
		DH_get0_key(d2, &d2pub_key, &d2priv_key);

//		print_bigdata(d2p,"d2p");
//		print_bigdata(d2pub_key,"d2pub_key");
//		print_bigdata(d2priv_key,"d2priv_key");

		// ���㹲����Կ:d1+d2pub_key,d2+d1pub_key������ͬ�Ĺ�����Կ
		unsigned char sharekey1[1024] = {0};
		unsigned char sharekey2[1024] = {0};
		int len1=DH_compute_key(sharekey1,d2pub_key,d1);
		int len2=DH_compute_key(sharekey2,d1pub_key,d2);
		if(len1!=len2)
		{
			printf("���ɹ�����Կʧ��\n");
			return -1;
		}
		if(memcmp(sharekey1,sharekey2,len1)!=0)
		{
			printf("���ɹ�����Կʧ��\n");
			return -1;
		}

//		print_hexdata(sharekey1, len1, "sharekey1");
//		print_hexdata(sharekey2, len2, "sharekey2");

		DH_free(d1);
		DH_free(d2);
		return 0;
	}




	static unsigned char dh_g_2[] = {0x02};

	static unsigned char dh_pa_768[] = {
		0xa5,0x2b,0xb2,0x89,0xd6,0xc9,0x1a,0x25,0x2f,0xca,0x89,0x52,0x51,0x2a,0x00,0x1e,
		0xd9,0x3d,0x92,0x50,0x58,0xa3,0x8e,0x23,0x7a,0x98,0x85,0xe1,0x5b,0x98,0x06,0x2f,
		0x7e,0xd2,0x21,0x01,0xa4,0x67,0xc9,0x5a,0x1a,0x12,0x9c,0x96,0x4a,0x08,0x75,0x8c,
		0xb9,0xb4,0x46,0xc1,0x62,0x76,0xbc,0xdb,0xe9,0xdd,0xbc,0x2d,0x5e,0x78,0x90,0xe7,
		0x52,0x50,0x27,0x3c,0xad,0x88,0x9c,0xc3,0xac,0x8b,0x91,0x52,0x7f,0x10,0x35,0xb2,
		0xb5,0x20,0x8f,0x6b,0x81,0xab,0xbe,0x07,0x1c,0x8e,0x42,0x9d,0x16,0x9e,0x65,0xdb
	};

	static unsigned char dh_xa_768[] = {
		0x72,0xb2,0x3d,0x8b,0xa1,0x2a,0x89,0x72,0x56,0xd0,0x44,0xe6,0x60,0x3a,0x79,0x0d,
		0x70,0x85,0xa1,0xef,0xc1,0x99,0x7c,0xc8,0x4d,0x5d,0x16,0x46,0xae,0x7d,0xf8,0xa8,
		0x25,0x61,0xd1,0x4d,0x9a,0x9a,0x2d,0xe0,0x56,0x2f,0x9f,0x49,0x9a,0x07,0xf0,0x37,
		0xc9,0x15,0xa5,0x4d,0x88,0x5a,0x1a,0x10,0xac,0xa5,0xbe,0xeb,0x74,0xa6,0x05,0x67,
		0x9e,0x78,0x72,0x8f,0x22,0x78,0x6f,0x2f,0xb9,0x96,0x8f,0x13,0x57,0x88,0x4c,0x9f,
		0x67,0x37,0xe2,0x67,0x0d,0x4a,0xe8,0x30,0xde,0xa5,0xcf,0x19,0x88,0x20,0x82,0x78
	};

	static unsigned char dh_except_a_pubkey_768[] = {
		0x44,0x2a,0xc0,0xc0,0xd0,0x38,0xa4,0x33,0x23,0x1c,0x52,0x17,0xdd,0x9d,0x91,0x03,
		0x75,0xc7,0x51,0xe3,0x86,0x1d,0x11,0xad,0xdf,0x6d,0x6f,0x2c,0xf4,0x9b,0x0e,0x62,
		0x86,0x22,0xdc,0x35,0x1b,0x91,0x45,0x63,0x3a,0x10,0xbc,0x94,0xd9,0xf7,0xb2,0x65,
		0x2e,0x62,0x03,0x9e,0x5f,0x65,0x4a,0xa1,0x91,0x44,0x0b,0x32,0x81,0xf1,0x6f,0x1b,
		0x58,0xe7,0xa6,0x79,0xd6,0x30,0xf4,0xd0,0xc9,0xbc,0x52,0x1a,0xf9,0x34,0x39,0x68,
		0xcf,0x7b,0x14,0x84,0x57,0x32,0xf0,0x4a,0xbf,0x03,0xc6,0x48,0x19,0x35,0xde,0xab
	};

	static unsigned char dh_pb_768[] = {
		0xa5,0x2b,0xb2,0x89,0xd6,0xc9,0x1a,0x25,0x2f,0xca,0x89,0x52,0x51,0x2a,0x00,0x1e,
		0xd9,0x3d,0x92,0x50,0x58,0xa3,0x8e,0x23,0x7a,0x98,0x85,0xe1,0x5b,0x98,0x06,0x2f,
		0x7e,0xd2,0x21,0x01,0xa4,0x67,0xc9,0x5a,0x1a,0x12,0x9c,0x96,0x4a,0x08,0x75,0x8c,
		0xb9,0xb4,0x46,0xc1,0x62,0x76,0xbc,0xdb,0xe9,0xdd,0xbc,0x2d,0x5e,0x78,0x90,0xe7,
		0x52,0x50,0x27,0x3c,0xad,0x88,0x9c,0xc3,0xac,0x8b,0x91,0x52,0x7f,0x10,0x35,0xb2,
		0xb5,0x20,0x8f,0x6b,0x81,0xab,0xbe,0x07,0x1c,0x8e,0x42,0x9d,0x16,0x9e,0x65,0xdb
	};

	static unsigned char dh_xb_768[] = {
		0x5b,0xe7,0xa0,0xd2,0xd2,0xd0,0x25,0x83,0x5a,0xe2,0x35,0x20,0x05,0x61,0x51,0x42,
		0x2a,0x8d,0x89,0xd8,0x94,0x85,0x84,0x42,0x3d,0x09,0x6a,0x18,0x1e,0x7a,0x71,0xa0,
		0xb6,0x33,0x67,0x24,0x59,0x8d,0x21,0x2d,0x16,0xfa,0x0b,0x20,0x5b,0x14,0x9f,0x69,
		0x2c,0x56,0xce,0x67,0xeb,0x6d,0x11,0x25,0x45,0x94,0x13,0x5f,0x49,0x77,0xc3,0x36,
		0x07,0x90,0xad,0xbf,0xa5,0xb8,0x04,0x54,0x42,0xdb,0xfa,0xfa,0x43,0x05,0x41,0xe0,
		0xa5,0x87,0xd3,0x59,0x3e,0x2a,0xb0,0x8c,0x47,0x6f,0x27,0xc0,0x07,0x27,0x97,0x04
	};

	static unsigned char dh_except_b_pubkey_768[] = {
		0x73,0xf7,0x1a,0xd1,0x2a,0xd0,0xe0,0x0e,0xf6,0xee,0x74,0xfd,0x3a,0xb5,0xd2,0xca,
		0xb8,0x23,0xe4,0xce,0xc3,0x9a,0xbb,0xe8,0x9b,0xbf,0x67,0xbf,0x0f,0x51,0xe6,0x7d,
		0x20,0x12,0xf9,0x84,0x99,0xf6,0xd3,0xae,0xbf,0x7a,0x32,0x94,0x2d,0xb5,0x97,0x3b,
		0x12,0xf9,0x03,0xcd,0x89,0xb6,0xdf,0xb8,0x6b,0x00,0xc3,0x1d,0x44,0x8c,0x28,0xa0,
		0xd2,0x4a,0x76,0xeb,0x86,0x32,0x7b,0xa6,0x39,0x49,0x8e,0x7b,0x3a,0x3e,0xe5,0x75,
		0x07,0xaf,0x27,0x27,0xd1,0xdd,0x5d,0x16,0xd7,0x2c,0x3b,0x7e,0x5d,0x8e,0x78,0x2e
	};

	static unsigned char dh_share_key_768[] = {
		0x64,0x01,0xfa,0x30,0x1c,0x96,0x7a,0x51,0xe7,0x53,0x8b,0xda,0x78,0x79,0xa1,0xce,
		0xea,0x63,0x91,0x89,0xea,0xce,0xe2,0x41,0xc2,0x85,0x1f,0x2d,0xd1,0xbf,0xca,0x22,
		0x7c,0x11,0x3e,0x69,0xb9,0x59,0x20,0x95,0x5b,0xe2,0x96,0xf7,0x39,0x69,0xe8,0xb2,
		0x65,0xac,0xa2,0x7f,0x2c,0x7b,0x7b,0x54,0xa4,0x44,0xd7,0xa1,0xc7,0xf3,0x38,0xde,
		0x11,0x03,0xbf,0x53,0x7e,0x4e,0x37,0x17,0x26,0x8a,0xc3,0x92,0x7c,0x83,0x2c,0xcb,
		0xd1,0xb3,0xd8,0x96,0x7d,0x0f,0x35,0x6c,0x47,0x6a,0x30,0xde,0x25,0x66,0x29,0x3d
	};

	int dh2_main()//���������ݳ�ʼ��
	{
		int key_bits = 768;
		int ret;
		// ����DH���ݽṹ
		DH *d1 = NULL;
		d1=DH_new();
		BIGNUM *p, *g, *pri1;
	    p  = BN_bin2bn(dh_pa_768, sizeof(dh_pa_768), NULL);//������һ������ΪNULL����һ���µ�
	    g = BN_bin2bn(dh_g_2, sizeof(dh_g_2), NULL);
		pri1 = BN_bin2bn(dh_xa_768, sizeof(dh_xa_768), NULL);
		BIGNUM *t_p = NULL, *t_g = NULL;
		t_p=BN_dup(p);
		t_g=BN_dup(g);
		DH_set0_pqg(d1, t_p, NULL, t_g);
		DH_set0_key(d1, NULL, pri1);

		ret=DH_generate_key(d1);
		if(ret!=1)
		{
			printf("DH_generate_key err!\n");
			return -1;
		}

		// ��ȡd1��p,g,pub_key,pri_key
//		const BIGNUM *d1p = NULL, *d1g = NULL;
//		DH_get0_pqg(d1, &d1p, NULL, &d1g);
		const BIGNUM *d1pub_key = NULL, *d1priv_key = NULL;
		DH_get0_key(d1, &d1pub_key, &d1priv_key);

//		print_bigdata(d1p,"d1p");
//		print_bigdata(d1pub_key,"d1pub_key");
//		print_bigdata(d1priv_key,"d1priv_key");


		DH *d2 = NULL;
		d2=DH_new();
		BIGNUM *pub2,*pri2;

		pub2 = BN_bin2bn(dh_except_b_pubkey_768, sizeof(dh_except_b_pubkey_768), NULL);
		pri2 = BN_bin2bn(dh_xb_768, sizeof(dh_xb_768), NULL);
		DH_set0_pqg(d2, t_p, NULL, t_g);
		DH_set0_key(d2, pub2, pri2);

		ret=DH_generate_key(d2);
		if(ret!=1)
		{
			printf("DH_generate_key err!\n");
			return -1;
		}

		// ��ȡd2��p,g,pub_key,pri_key
//		const BIGNUM *d2p = NULL, *d2g = NULL;
//		DH_get0_pqg(d2, &d2p, NULL, &d2g);
		const BIGNUM *d2pub_key = NULL, *d2priv_key = NULL;

		//ʹ��ǰ���Ѿ��еĹ�Կ������
		d2pub_key=pub2;
//		DH_get0_key(d2, &d2pub_key, &d2priv_key);


//		print_bigdata(d2p,"d2p");
//		print_bigdata(d2pub_key,"d2pub_key");
//		print_bigdata(d2priv_key,"d2priv_key");

		// ���㹲����Կ:d1+d2pub_key,d2+d1pub_key������ͬ�Ĺ�����Կ
		unsigned char sharekey1[1024] = {0};
		unsigned char sharekey2[1024] = {0};
		int len1=DH_compute_key(sharekey1,d2pub_key,d1);
		int len2=DH_compute_key(sharekey2,d1pub_key,d2);
		if(len1!=len2)
		{
			printf("���ɹ�����Կʧ��\n");
			return -1;
		}
		if(memcmp(sharekey1,sharekey2,len1)!=0)
		{
			printf("���ɹ�����Կʧ��\n");
			return -1;
		}

//		print_hexdata(sharekey1, len1, "sharekey1");
//		print_hexdata(sharekey2, len2, "sharekey2");

		return 0;
	}
	int main(int  argc, char* argv[]){
		/*
		//--hash
		sha1();
		sha256();
		md5();

		//--�Գ�
		des_ncbc();//DES���AES

		//--�ǶԳ�
		//RSA,DSA
*/
		//--DH
		dh_main();
		dh2_main();
		//--HMAC
		
		//--EVP
		
		return 0;
	}

};
