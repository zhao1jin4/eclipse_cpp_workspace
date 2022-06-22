CFLAGS = -Iadd -Isub -O2 -g
#也可make CC=g++
#CC=g++

TARGET = calc
 

#=====不用VPATH　１
#使用export向子目录的makefile传递变量
export DEST_DIR=${shell pwd}/out

DIRS=sub add .
#foreach 格式为var,list,item_out
#wildcard 可用*匹配
FILES=$(foreach dir ,$(DIRS),$(wildcard $(dir)/*.c)) 
#patsubst格式　pattern,replacement,in_text
OBJS=$(patsubst %.c,%.o,$(FILES))

#默认找第一个规则 
$(TARGET): $(DEST_DIR) main.o
	#(cd add && $(MAKE))#要使用shell命令外要加(　)
	(cd add ; $(MAKE))#也可用;分隔
	#$(MAKE) -C add #大写的Ｃ
	$(MAKE) -C sub
	#$(CC) -o $(TARGET) $(DEST_DIR)/*.o  #依赖不能用* ???
	$(CC) -o $(TARGET) $(OBJS)
	
$(DEST_DIR):
	mkdir -p $(DEST_DIR)
	
#VPATH　搜索add和sub目录
#VPATH=add:sub　
#=====用VPATH
#OBJS = add_int.o add_float.o sub_int.o sub_float.o main.o

#--方式一 用VPATH
#$(TARGET):$(OBJS) #依赖.ｏ,.ｏ会自动根据.ｃ生成
#	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)　#必须tab键开头是命令，可用\分隔多行

 #--方式二 用VPATH
#$(TARGET): $(OBJS)
#目标是多个，每个都做相同的事。把所有依赖于.o替换为依赖于.c
#$(OBJS): %.o: %.c 
	#$<依赖的第一个，此处为maic.c　，$@　依赖的目标，此处为calc
#	$(CC) -c $(CFLAGS) $< -o $@  

#--方式三　用VPATH
#$(TARGET): $(OBJS)
#	#$^所有不重复的依赖列表
#	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	-$(RM) $(TARGET)  #前加"-"表示如果出错继续执行
	-$(RM) $(OBJS)

