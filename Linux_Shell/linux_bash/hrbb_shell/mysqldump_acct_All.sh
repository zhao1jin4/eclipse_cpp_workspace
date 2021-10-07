#!/usr/bin/bash

#this shell place in .21 server , dir: /home/creditpush/mysqldump 

rootDir=/home/creditpush/mysqldump

now=`date +"%Y-%m-%d_%H-%M-%S"`

echo "begin backup accounting ${now} --"
/usr/bin/mysqldump -ucreditpush -pcreditpush -h 35.8.33.11 --add-drop-database=false --disable-keys accounting > ${rootDir}/accounting-full_${now}.sql
now1=`date +"%Y-%m-%d_%H-%M-%S"`
echo "end backup accounting   ${now1}"


echo "begin gzip accounting ${now1}  -- "
gzip  ${rootDir}/accounting-full_${now}.sql
now2=`date +"%Y-%m-%d_%H-%M-%S"`
echo "end gzip accounting   ${now2}"

function calcDiffDay(){
        first=`date --date="$1" +%s`
		second=`date --date="$2" +%s`
        plusRes=`expr $first - $second`
        diff=`expr "scale=0;$plusRes / 3600 / 24"|bc`
		return $diff
}

echo " begin check delete file in ${rootDir} ,where day <28 and diffDay >15 ${file}  "

current_date=`date +"%Y-%m-%d"`
for filePath in `ls ${rootDir}/accounting-full_*.sql.gz` ;do
	fileItem=${filePath##*/}
   	dateStr=${fileItem:16:10}
    day=${dateStr##*-}
    calcDiffDay $current_date $dateStr
    diffDay=$?
    if [ $day -lt 28 -a  $diffDay -gt 15 ]; then
           echo " delete file ${filePath} ready"
           rm   ${filePath}
           echo " delete file ${filePath} done"
    fi
done
echo " end check delete"
