#yum install dialog

dialog --msgbox "hello" 9 18  ##(高，宽)，要点一下OK

dialog --title "confirm" --yesno "Are you willing to take part ?" 9 18
#选 yes $?返回0,no $?返回1
if [ $? != 0 ] ; then
        dialog --infobox "OK" 5 20  #立即退出实时交互
        sleep 2
        dialog --clear
        exit 0
fi 

#多选checklist
dialog --title "check Me" --checklist "pick number" 15 25 3 1 "one" "off"  2 "two" "on" 3 "three" "off" 2>res.txt
#结果输出到标准错误中,3表示3组

dialog --title "question" --inputbox "enter your age" 9 30 2>res.txt

#单选menu
dialog --title "music " --menu "select you love music" 15 30 4 1 "classical" 2 "JAzzy"  3 "Country" 4 "other" 2>res.txt



