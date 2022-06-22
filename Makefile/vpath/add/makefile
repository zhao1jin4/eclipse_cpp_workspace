
add:
	$(CC) -xc++ -c add_int.c add_float.c  #gcc -xc++  表示Ｃ＋＋语言
	echo  "coming var DEST_DIR = $(DEST_DIR)" #使用父级传来的变量

#OBJS = add_int.o add_float.o
#add:$(OBJS)
#$(OBJS):%.o:%.c
#	$(CC) -c %< -o $(DEST_DIR)/$@ 		#%<不能被解析？？？
 
#----SUFFIXES 以下没有效果　？？？
#add: add_int.o add_float.o
#没作用？？
#.SUFFIXES: .cpp
#.cpp.o:
#	$(CC) -xc++ $(CFLAGS) -c $< 
#
#--二选一不行？
#%.cpp: %.o #书上是%o ,没有点，这个不能合上面的　SUFFIXES　.cpp.o一起用
#	$(CC) -xc++ $(CFLAGS) -c $<  　


 