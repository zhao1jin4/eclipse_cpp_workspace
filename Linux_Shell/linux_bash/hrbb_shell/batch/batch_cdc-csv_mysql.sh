#!/usr/bin/bash
readDir=/home/hrbfex/file/CDC
mysqlHost=35.8.33.11
mysqlOSUser=pettyloan
#mysqlOSPass=hrbb@123
mysqlUser=cdcquery
mysqlPass=cdcquery

csvHost=35.8.33.22
csvOSUser=pettyloan
#csvOSPass=


cd $readDir
yesterday=`date -d"-1 day" "+%Y%m%d"`
#yesterday=20150714

yesterdayBefore=`date -d"-2 day" "+%Y%m%d"`

mainFile=CBS_PUBTRANDEF_${yesterday}.dat 
extFile=CBS_PUBTRANEXT_${yesterday}.dat 
now=`date +"%Y-%m-%d %H:%M:%S"`


#mysql -h $mysqlHost -u$mysqlUser -p$mysqlPass -Dcdcquery -e "select count(*) from pubtrandef where trandate=date_format(date_add(now(), interval -1 day),'%Y-%m-%d')"

echo "=========${now} start cron job , yesterday={yesterday} delete  yesterday before day file ${readDir}/${yesterdayBefore}.* file "
rm -rf ${yesterdayBefore}.*

if [ ! -e  $readDir/${mainFile}  ] ; then
	echo "yesterday  file  $readDir/${mainFile}  not upload ,not process"
	exit 0
fi

if [ -e  "${readDir}/${yesterday}.done"  ] ; then
      echo "found ${yesterday}.done file not process"
      exit 0
fi

echo "no file ${yesterday}.done ,touch ${yesterday}.tmp file ,begain process data\n"
touch ${readDir}/${yesterday}.tmp

echo "connect to mysql"
mysql -h $mysqlHost -u$mysqlUser -p$mysqlPass -Dcdcquery <<EOF
	system echo "delete data from  batch_pubtrandef_tmp"
	truncate  batch_pubtrandef_tmp ;
-- delete from  batch_pubtrandef_tmp where trandate=date_format(date_add(now(), interval -2 day),'%Y-%m-%d');
	commit;

	system echo "delete data from batch_pubtranext_tmp"
 	truncate  batch_pubtranext_tmp;
-- delete from  batch_pubtranext_tmp  where trandate=date_format(date_add(now(), interval -2 day),'%Y-%m-%d');
	commit;


	system echo "loading data from file ${mainFile} to table batch_pubtrandef_tmp"
	load data local infile '${readDir}/${mainFile}' into table batch_pubtrandef_tmp  CHARACTER SET gbk FIELDS TERMINATED BY '/'   LINES TERMINATED BY '\n' ;
	commit;

	system echo "loading data rom file ${extFile} to table batch_pubtranext_tmp"
	load data local infile '${readDir}/${extFile}' into table batch_pubtranext_tmp  CHARACTER SET gbk FIELDS TERMINATED BY '/'   LINES TERMINATED BY '\n' ;
	commit;

	system echo "loading data to tmp table  done"
	
	
    system echo "------repay----- copying filter table data  from batch_pubtrandef_tmp to repay_batch_pubtrandef "

     insert into   repay_batch_pubtrandef SELECT  d.*
     FROM  batch_pubtrandef_tmp d
     where 
     d.craccount in (
	'680101416030010000',
	'680101416030010001',
	'680101416030010003',
	'680101416030010004',
	'680101416030010005',
	'680101416030010006',
	'680101416030010007',
	'680101416030010009',
	'680101416030010010',
	'680101416030010011',
	'680101416030010012',
	'680101416030010013',
	'680101416030010014',
	'680101416030010017',
	'680101416030010018',
	'680101416030010020'
	);
	commit;



	system echo "------repay----- copying filter  table data from  batch_pubtranext_tmp to repay_batch_pubtranext"

  	insert into   repay_batch_pubtranext  SELECT  e.*
     FROM  batch_pubtrandef_tmp d,  batch_pubtranext_tmp e
     where
     d.batchno= e.batchno and d.memocode=e.memocode and d.keyword=e.keyword
	   and   d.craccount in (
	'680101416030010000',
	'680101416030010001',
	'680101416030010003',
	'680101416030010004',
	'680101416030010005',
	'680101416030010006',
	'680101416030010007',
	'680101416030010009',
	'680101416030010010',
	'680101416030010011',
	'680101416030010012',
	'680101416030010013',
	'680101416030010014',
	'680101416030010017',
	'680101416030010018',
	'680101416030010020'
	);
	
	commit;



	system echo "-------payin---- copying filter table data  from batch_pubtrandef_tmp to payin_batch_pubtrandef "

     insert into   payin_batch_pubtrandef SELECT  d.*
     FROM  batch_pubtrandef_tmp d
     where 
     d.craccount in ( 
    '680101416030010002',
     '680101416030010008',
     '680101416030010015',
     '680101416030010019',
     '680101416030010021'
	) or d.dbaccount in (
	 '680101416030010002',
     '680101416030010008',
     '680101416030010015',
     '680101416030010019',
     '680101416030010021'
	);
	commit;

	system echo "-----payin------ copying filter  table data from  pubtranext_tmp to payin_batch_pubtranext"

  	insert into   payin_batch_pubtranext  
  	SELECT  e.*
    FROM  batch_pubtrandef_tmp d,  batch_pubtranext_tmp e
     where
     d.batchno= e.batchno and d.memocode=e.memocode and d.keyword=e.keyword
   	and(
	   		d.craccount in 
		   	( 
		   	 '680101416030010002',
		     '680101416030010008',
		     '680101416030010015',
		     '680101416030010019',
		     '680101416030010021'
			) or d.dbaccount in 
			(
			 '680101416030010002',
		     '680101416030010008',
		     '680101416030010015',
		     '680101416030010019',
		     '680101416030010021'
			)
		);

	commit;
	
	system echo "----------- copy filter data  done"
	
	
	system mv  ${readDir}/${yesterday}.tmp ${readDir}/${yesterday}.done
	system echo "process day ${yesterday}  file done ,rename tmp file to done"

EOF





