obj-m += example.o
#obj-m ?= example.o
#example.c生成example.o后,再生成 example.ko

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	#-C 执行任何这前先进入这个目录 ,是一个链接到 /usr/src/kernels/$(shell uname -r)
	#M=
	#modules是make命令的目标(target)参数
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean