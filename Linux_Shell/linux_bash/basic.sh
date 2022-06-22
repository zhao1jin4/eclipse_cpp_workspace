#!/usr/bin/bash

foo=1 
while [ ${foo} -le 20 ]
do
	echo "while add one,foo=${foo}" 
	
	#赋值
	foo=$((foo+1))
done


foo=1 
#until与while相反，until是条件不成立时执行
until [ ${foo} -le 20 ]
do
	echo "until add one,foo=${foo}"  
	foo=$((foo+1))
done

echo "Is it morning? type yes/no/unknown" 
read noon
case ${noon} in 
	[yY]*) echo "yes ,morning" ;;
	[nN]*) echo "no ,afternoon" ;; 
	#这是单坚线
	u*|U*) echo "i don't know" ;;
	*) echo "wrong type in" ;;
esac



myfunc(){
	#这是双坚线，与用 ＆＆
	if [ -f hello.txt ] || [ -f word.txt ] ;then
		printf "hello.txt  or world.txt in this dir \n"
	else
		printf "can not found hello.txt  or world.txt in this dir \n"
	fi
}
#调用不用加（）
myfunc

#$()和``一样
res=$(myfunc) #可以把函数中的echo或printf当返回值
echo "res=${res}"




calc(){
	echo "all @ param=" $@
	echo "all * param=" $*
#局部变量
 local	i=1
   while : #死循环 while : 同while true  
	do
		i=$((i+1))
		if [ $i -gt 10 ] ;then
			break #对应的有coninue 
		fi
		echo "i=$i"
	done 
	
	printf "program name=$0 , param1=$1\n"
	
	#return `expr $1 + $2` #expr 的取值要用 `` 或 $( ) 
	#return $(expr $1 + $2) #`` 可用 ()  替代
	
	return $(( $1 + $2)) #expr 可用 $(( )) 用于算术
	
}
set $(date) #从这开始，date命令的输出做为参数，即可$2取月
echo "this month is $2"
 
calc 11 22
echo "calc return $?"

echo current dir is ${PWD} #取变量
echo current dir is $PWD #取变量
echo login user is $(who) #执行命令

foo=10
x=foo
eval y='$'$x
echo $y;


#exec ip a s # 运行后启动新的shell,代替原shell, 后面脚本不会被执行
#echo "HERE NOT REACHED"


shift #参数左移一个，即$2 变为 $1　($0不变)
echo "after shift month=$1"

#trap -l 显示信号关系名称,使用时要省略SIG前缀,如SIGHUP要使用HUP
#格式为 trap <command> <signal> ,当收到信号时做指定动作,如要恢复默认值command前加-,如要忽略信号，信号传''
#find ./ \(-name *.txt ||  -newer ./VPN.txt \) -type f  -print
#find ./ \(-name *.txt && -newer ./VPN.txt \) -type f  -print
#grep -E [a-z]{10} VPN.txt #即{ }也可不转议
#grep -E Th.[[:blank:]] xx.txt

#echo ${Vname:+value}如果Vanme有过设置,显示value的值,否则空
#echo ${Vname:?value}如果Vanme没有设置,显示错误的value的信息,		否则显示Vname 的值
#echo ${Vname:-value}如果Vanme没有设置,显示value的值,			否则显示Vname 的值
#echo ${Vname:=value}如果Vanme没有设置,设置Vanme的值value,并显示,	否则显示Vname 的值
#
#echo ${#Vname}  Vname的长度
#echo ${Vname%value}  从Vnam尾删与value匹配最小
#echo ${Vname%%value} 从Vnam尾删与value匹配最大
#echo ${Vname#value}  从Vnam头删与value匹配最小
#echo ${Vname##value} 从Vnam头删与value匹配最大
#
#${varible##*string} 从左向右截取最后一个string后的字符串
#${varible#*string}  从左向右截取第一个string后的字符串
#${varible%%string*} 从右向左截取最后一个string后的字符串
#${varible%string*}  从右向左截取第一个string后的字符串



exit 0

