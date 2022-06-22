#make -p 先执行make命令,再显示内置规则

UNAME = $(shell uname)
first:  #make 命令默认执行第一个规则

	echo "OS=$(OS)" #是空的
ifeq ($(OS),Windows_NT)#可以条件
	RM=del
    echo "Windows"
else
	RM=rm
	echo "not Windows"
endif


ifeq ($(UNAME), Linux)
	echo "Linux"
endif
ifeq ($(UNAME), Solaris)
	echo "Solaris"
endif



	
	
	
	echo "MAKE=$(MAKE)"
	
	echo "AR=$(AR)"
	echo "AS=$(AS)"
	echo "CC=$(CC)"
	echo "CPP=$(CPP)"
	echo "CXX=$(CXX)"
	echo "RM=$(RM)"
	#以下没有默认值
	echo "CLAGS=$(CLAGS)"
	echo "CPPLAGS=$(CPPLAGS)"
	echo "CXXFLAGS=$(CXXFLAGS)"
	echo "ARFLAGS=$(CXXFLAGS)"
	echo "ASFLAGS=$(CXXFLAGS)"
	
	