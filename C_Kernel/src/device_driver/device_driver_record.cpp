/*
对于内核来说，C++在运行时太大了

ls -l /dev/ c开头字符设置,b开头块设备
格式mknode name c/b 主版本  次版本,如 mknod /dev/mylp0 c 6 0
kernel-devel 软件包

内核编程下
#include  <linux/module.h> 引用的是 /usr/src/kernels/5.11.12-300.fc34.x86_64/include/linux/module.h 不是 /usr/include/linux/module.h
#include  <linux/kernel.h> 引用的是 /usr/src/kernels/5.11.12-300.fc34.x86_64/include/linux/kernel.h

/usr/src/kernels/5.11.12-300.fc34.x86_64/include/asm-generic/
/usr/src/kernels/5.11.12-300.fc34.x86_64/arch/

grep sprintf /proc/kallsyms

*/

#include  <linux/module.h>
#include  <linux/kernel.h>

 #include <linux/types.h>
#include <asm/posix_types.h>

 #include <linux/fs.h>
void type(){
regitser_chrdev();
//在32位系统和64位系统中数据类型(如int)长度是不一样的
__u8 len=0; //定义在 <linux/types.h> 或  <asm/posix_types.h>
__u32 size=0;//长度是固定的,不同平台做对应的

//size_t x;
//ssize_t y;

//KERN_DEBUG在<linux/kern_levels.h>里定义
//printk(KERN_DEBUG "Hello, kernel!\n");

register_chardev();

}
