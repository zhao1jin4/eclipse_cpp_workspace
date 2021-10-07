#!/usr/bin/bash

mysqlHost=35.8.33.11
mysqlOSUser=pettyloan
#mysqlOSPass=hrbb@123
mysqlUser=cdcquery
mysqlPass=cdcquery
writeCSVDir=/home/cdc/CDC
#today=`date +"%Y%m%d"`
yesterday=`date -d"-1 day" "+%Y%m%d"`

now=`date +"%Y-%m-%d %H:%M:%S"`
echo "=========${now} start cron job"


batchMysql2CSV ()
{
	sqlfile=$1
	destfile=$2
	if [  -e  "${writeCSVDir}/${destfile}"  ] ; then
	        echo "yesterday file ${destfile} has exist ,not process"
	        exit 0
	fi
	
	echo "begin export  yesterday csv file ${writeCSVDir}/${destfile}.utf-8 file "
	mysql -h $mysqlHost -u$mysqlUser -p$mysqlPass -Dcdcquery < `dirname $0`/${sqlfile} | sed 's/\t/,\t/g;s/$/\r/g' > ${writeCSVDir}/${destfile}.utf-8
	echo "export yesterday csv ${destfile}.utf-8 done"
	
	echo "begin convert csv file utf-8 to gbk ,generate new file ${writeCSVDir}/${destfile} "
	iconv -f UTF-8 -t GBK ${writeCSVDir}/${destfile}.utf-8 > ${writeCSVDir}/${destfile}
	echo "convert ut-8 to gbk done"
	
	echo "begin delete yesterday ${writeCSVDir}/${destfile}.utf-8 file "
	rm ${writeCSVDir}/${destfile}.utf-8
	echo "delete yesterday ${writeCSVDir}/${destfile}.utf-8 file done"
}

batchMysql2CSV  RepayBatchMysql2CSV.sql repay_${yesterday}.csv
batchMysql2CSV  PayinBatchMysql2CSV.sql payin_${yesterday}.csv 


