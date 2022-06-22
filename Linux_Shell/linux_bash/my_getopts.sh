while getopts ahfvc: OPTION   ###-a -h  或者-ah ,(:表示有值的-c 123,如-c=33,值是=33)
do
	case $OPTION in
		a)
			echo "a"
		;;
		h)
			echo "h"
		;;
		c)
			x=$OPTARG        ##得到参数的值
			echo "c= $x"
		;;
		\?)
			echo "未知选项"
		;;
	esac
done
echo total $OPTIND options and arg #$OPTIND 最后一个下标

echo $(($OPTIND -1))
#shift ｀expr $OPTIND -1｀
shift $(($OPTIND -1))

echo other command arg is :$*

#不能传没有的选项报错，./my_getopts.sh  -ah -w -c "c1c2"  xxx yy ,但也会继续执行 
#./my_getopts.sh  -i -ah -c "c1c2"  xxx yy
