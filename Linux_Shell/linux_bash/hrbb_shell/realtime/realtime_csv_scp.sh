#!/bin/bash

host=35.8.33.21
user=pettyloan
remoteDir=/home/cdc/CDC

now=`date +"%Y-%m-%d %H:%M:%S"`
echo "=========${now} start db2 scp cron job"

scpItem()
{
	csvFile=$1
	
	if [ ! -e /tmp/${csvFile} ] ; then
		echo "file /tmp/${csvFile} not exists ,not scp , contine next file"
		return 
	fi
	
	echo "beging scp  from db server /tmp/${csvFile} to  ${host}:${remoteDir}"
	scp /tmp/${csvFile}  ${user}@${host}:${remoteDir} 
	echo "scp done"
}
scpItem cdc_realtime_repay.csv
scpItem cdc_realtime_payin.csv

scpItem cdc_realtime_come.csv
scpItem cdc_realtime_go.csv

scpItem cdc_realtime_counter.csv
 


