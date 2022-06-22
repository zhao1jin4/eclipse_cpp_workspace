//#include <linux/init.h>
#include <linux/module.h> //这个里面有引入   <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");//版权信息,不加编译报错
MODULE_AUTHOR("abc");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

//static 和 __init
static int __init  example_init(void) {
	printk(KERN_INFO "Hello, World!\n");//printk 函数, 参数间不带逗号,KERN_INFO 也有 KERN_DEBUG
	return 0;
}
//static 和 __exit
static void __exit  example_exit(void) {
	printk(KERN_INFO "Goodbye, World!\n");
}

module_init(example_init);//被始使用,内核只执行一次
module_exit(example_exit);//内核在称除时调用一次,回收空间


/*
make 后生成文件有 example.o,example.mod.c,example.mod.o,example.ko,example.mod

sudo insmod example.ko #安装模块以.ko结尾的实际文件
lsmod  | grep example  #也在最上面,,也可以用 cat /proc/modules  | grep example,生成 /sys/module/example/ 目录
dmesg 可以看到代码的日志
sudo rmmod  example  #卸载模块是名字,不以.ko结尾, 也有日志
*/


