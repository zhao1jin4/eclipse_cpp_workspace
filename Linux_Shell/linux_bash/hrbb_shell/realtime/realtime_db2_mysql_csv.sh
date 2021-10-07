#!/bin/bash

#localCSVDir=/home/cdc/CDC
localCSVDir=/home/db2inst1/cdcquery

mysqlHost=35.8.33.11
mysqlUser=cdcquery
mysqlPass=cdcquery
mysqlDB=cdcquery


db2User=db2inst1
db2Pass=db2inst1
db2Alias=db2inst1
#db2Host=35.8.33.25


today=`date +"%Y-%m-%d"`
now=`date +"%Y-%m-%d %H:%M:%S"`
echo "==${now}== start cron job "

exportDB2_CSV()
{
	#db2 connect to ${db2Alias} user ${db2User} using ${db2Pass}
	. ~/sqllib/db2profile
	~/sqllib/bin/db2 <<EOF
	
	!echo " ----------begin connect to db2 cdcquery database  "
	 connect to  cdcquery
	 
	 !echo " ------repay------begine export db2 table pubtrandef   to csv file ${localCSVDir}/db2_repay_pubtrandef.csv  "
	 export to ${localCSVDir}/db2_repay_pubtrandef.csv of del  MODIFIED BY codepage=1208  \
			SELECT  d.*  \
			FROM  pubtrandef d  \
			 where   d.craccount in ( \
		'680101416030010000', \
		'680101416030010001', \
		'680101416030010003', \
		'680101416030010004', \
		'680101416030010005', \
		'680101416030010006', \
		'680101416030010007', \
		'680101416030010009', \
		'680101416030010010', \
		'680101416030010011', \
		'680101416030010012', \
		'680101416030010013', \
		'680101416030010014', \
		'680101416030010017', \
		'680101416030010018', \
		'680101416030010020' \
		) and d.modifytime >=current date
		
		! echo "------repay----- end export db2 table pubtrandef "
	
	
		!echo " -------repay------ begine export db2 table  pubtranext   to csv file  ${localCSVDir}/db2_repay_pubtranext.csv"
	
		  export to ${localCSVDir}/db2_repay_pubtranext.csv of del  MODIFIED BY codepage=1208  \
		SELECT  e.* \
			 FROM  pubtrandef d,  pubtranext e \
			 where  d.batchno= e.batchno and d.memocode=e.memocode and d.keyword=e.keyword \
			  and   d.craccount in ( \
		'680101416030010000', \
		'680101416030010001', \
		'680101416030010003', \
		'680101416030010004', \
		'680101416030010005', \
		'680101416030010006', \
		'680101416030010007', \
		'680101416030010009', \
		'680101416030010010', \
		'680101416030010011', \
		'680101416030010012', \
		'680101416030010013', \
		'680101416030010014', \
		'680101416030010017', \
		'680101416030010018', \
		'680101416030010020' \
		) and d.modifytime >=current date
		!echo "--------repay----- end export db2 table pubtranext "
		
		
		
		!echo " -------payin------ begine export db2 table  pubtrandef   to csv file  ${localCSVDir}/db2_payin_pubtrandef.csv"
	    export to ${localCSVDir}/db2_payin_pubtrandef.csv of del  MODIFIED BY codepage=1208  \
	    SELECT  d.* \
	    FROM  pubtrandef d  \
	     where  \
	    d.craccount in (  \
	    '680101416030010002',  \
	    '680101416030010008',  \
	    '680101416030010015',  \
	    '680101416030010019',  \
	    '680101416030010021'  \
		) or d.dbaccount in (  \
		'680101416030010002',  \
	    '680101416030010008',  \
	    '680101416030010015',  \
	    '680101416030010019',  \
	    '680101416030010021'  \
		) and d.modifytime >=current date   
		
		commit 
	
		!echo " -------payin------ begine export db2 table  pubtranext   to csv file  ${localCSVDir}/db2_payin_pubtranext.csv"
	    
	  	export to ${localCSVDir}/db2_payin_pubtranext.csv of del  MODIFIED BY codepage=1208  \
	  	SELECT  e.* \
	    FROM  pubtrandef d,  pubtranext e \
	    where \
	    d.batchno= e.batchno and d.memocode=e.memocode and d.keyword=e.keyword \
	   	and( \
		    d.craccount in (  \
		   	'680101416030010002', \
		    '680101416030010008', \ 
		    '680101416030010015', \
		    '680101416030010019', \
		    '680101416030010021' \
			) or   d.dbaccount in  \
			(   '680101416030010002', \
		    '680101416030010008', \
		    '680101416030010015', \
		    '680101416030010019', \
		    '680101416030010021' ) \
	    ) and d.modifytime >=current date  
	
		commit
		
		!echo "-----super net bank-----begin export db2 table  tbl_bcomecred  to db2_tbl_bcomecred.csv"
		export to ${localCSVDir}/db2_tbl_bcomecred.csv of del  MODIFIED BY codepage=1208  \
	  	SELECT  *   from tbl_bcomecred where modifytime >= current date  
		
		!echo "-----super net bank-----begin export   db2 table tbl_bfrocred data  to db2_tbl_bfrocred.csv"
		export to ${localCSVDir}/db2_tbl_bfrocred.csv of del  MODIFIED BY codepage=1208  \
	  	SELECT  *   from tbl_bfrocred where modifytime >= current date  
		
	  	!echo "-----counter-----------begin export  db2 table glssubtranslog  to db2_counter_realtime_tran.csv"
	  	export to ${localCSVDir}/db2_counter_realtime_tran.csv of del  MODIFIED BY codepage=1208  \
	  	SELECT * FROM glssubtranslog a \
		WHERE a.cdflag = 'D' \
		AND a.subsys IN ('DPS', 'CMS') \
		AND exists  \
		( select 'X' \
	    from glssubtranslog b \
		where b.cdflag = 'C' \
	     AND b.transource = '12' \
	     and a.trandate = b.trandate \
	     and a.serseqno = b.serseqno \
	     And b.acctno in ('680101416030010000', \
					'680101416030010001', \
					'680101416030010003', \
					'680101416030010004', \
					'680101416030010005', \
					'680101416030010006', \
					'680101416030010007', \
					'680101416030010009', \
					'680101416030010010', \
					'680101416030010011', \
					'680101416030010012', \
					'680101416030010014', \
					'680101416030010017', \
					'680101416030010018', \
					'680101416030010020', \
					'680101416030010022') and b.modifytime >= current date   \
		) and a.modifytime >= current date

		!echo "----------- disconnect db2"
		connect reset
		quit

EOF
}
 
csv2MySQL()
{

	if [ ! -e ${localCSVDir}/db2_repay_pubtrandef.csv ] ; then 
		echo "${localCSVDir}/db2_repay_pubtrandef.csv not exist,db2 today no new data, not process"
		exit 0
	fi

# when use <<EOF ,in the area can not use functoin
mysql -h $mysqlHost -u$mysqlUser -p$mysqlPass -D$mysqlDB  <<EOF
        system echo "----repay------mysql delete  today old  data from repay_realtime_pubtrandef"
		delete from repay_realtime_pubtrandef  where modifytime >= CURRENT_DATE ;
		commit;
		system echo "mysql delete   repay_realtime_pubtrandef done"
		
		
		system echo "mysql delete   today old data  from repay_realtime__pubtranext"
		delete from repay_realtime_pubtranext  where modifytime >=  CURRENT_DATE ;
		commit;
		system echo "mysql delete   repay_realtime_pubtranext done"
		
		
		system echo "mysql loading ${localCSVDir}/db2_repay_pubtrandef.csv to table repay_realtime_pubtrandef"
		load data local infile '${localCSVDir}/db2_repay_pubtrandef.csv' into table repay_realtime_pubtrandef  CHARACTER SET utf8 FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"'  LINES TERMINATED BY '\n' ;
		commit;
		system echo "mysql loading repay_realtime_pubtrandef done"

		system echo "mysql loading ${localCSVDir}/db2_repay_pubtranext.csv to table  repay_realtime_pubtranext"
        load data local infile '${localCSVDir}/db2_repay_pubtranext.csv' into table repay_realtime_pubtranext  CHARACTER SET utf8  FIELDS TERMINATED BY ','  OPTIONALLY ENCLOSED BY '"'  LINES TERMINATED BY '\n' ;
        commit;
		system echo "mysql loading repay_realtime_pubtrandef done"
		
		
		system echo "----payin------mysql delete  today old   data from payin_realtime_pubtrandef"
		delete from payin_realtime_pubtrandef  where modifytime >=  CURRENT_DATE ;
		commit;
		system echo "mysql delete   payin_realtime_pubtrandef done"
		
		
		system echo "mysql delete  today old  data  from payin_realtime_pubtranext"
		delete from payin_realtime_pubtranext  where modifytime >= CURRENT_DATE;
		commit;
		system echo "mysql delete   payin_realtime_pubtranext done"
		
		system echo "mysql loading ${localCSVDir}/db2_payin_pubtrandef.csv to table payin_realtime_pubtrandef"
		load data local infile '${localCSVDir}/db2_payin_pubtrandef.csv' into table payin_realtime_pubtrandef  CHARACTER SET utf8 FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"'  LINES TERMINATED BY '\n' ;
		commit;
		system echo "mysql loading payin_realtime_pubtrandef done"

		system echo "mysql loading ${localCSVDir}/db2_payin_pubtranext.csv to table payin_realtime_pubtranext"
        load data local infile '${localCSVDir}/db2_payin_pubtranext.csv' into table payin_realtime_pubtranext  CHARACTER SET utf8  FIELDS TERMINATED BY ','  OPTIONALLY ENCLOSED BY '"'  LINES TERMINATED BY '\n' ;
        commit;
		system echo "mysql loading payin_realtime_pubtrandef done"
		
		system echo "----tbl_bcomecred------mysql delete today old   data from tbl_bcomecred"
		delete from tbl_bcomecred  where modifytime >=  CURRENT_DATE;
		commit;
		system echo "mysql delete   tbl_bcomecred done"
		system echo "mysql loading ${localCSVDir}/db2_tbl_bcomecred.csv to table tbl_bcomecred"
        load data local infile '${localCSVDir}/db2_tbl_bcomecred.csv' into table tbl_bcomecred  CHARACTER SET utf8  FIELDS TERMINATED BY ','  OPTIONALLY ENCLOSED BY '"'  LINES TERMINATED BY '\n' ;
        commit;
		system echo "mysql loading db2_tbl_bcomecred done"
		
		
		system echo "----tbl_bfrocred------mysql delete  today old   data  from tbl_bfrocred"
		delete from tbl_bfrocred  where modifytime >=  CURRENT_DATE;
		commit;
		system echo "mysql delete  tbl_bfrocred done"
		system echo "mysql loading ${localCSVDir}/db2_tbl_bfrocred.csv to table tbl_bfrocred"
        load data local infile '${localCSVDir}/db2_tbl_bfrocred.csv' into table tbl_bfrocred  CHARACTER SET utf8  FIELDS TERMINATED BY ','  OPTIONALLY ENCLOSED BY '"'  LINES TERMINATED BY '\n' ;
        commit;
		system echo "mysql loading tbl_bfrocred done"
		
		system echo "----counter_realtime_tran------mysql delete today old   data  from counter_realtime_tran"
		delete from counter_realtime_tran  where modifytime >=  CURRENT_DATE;
		commit;
		system echo "mysql delete  counter_realtime_tran done"
		system echo "mysql loading ${localCSVDir}/db2_counter_realtime_tran.csv to table counter_realtime_tran"
        load data local infile '${localCSVDir}/db2_counter_realtime_tran.csv' into table counter_realtime_tran  CHARACTER SET utf8  FIELDS TERMINATED BY ','  OPTIONALLY ENCLOSED BY '"'  LINES TERMINATED BY '\n' ;
        commit;
		system echo "mysql loading counter_realtime_tran done"
EOF
	echo "mysql loading done"
}

MySQL2FinalCSV()
{
	sqlFile=$1
	filePath=$2
	echo "-------begin export   csv file ${filePath}.utf8 file "
	mysql -h $mysqlHost -u$mysqlUser -p$mysqlPass -Dcdcquery --default-character-set=utf8 < ${sqlFile} | sed 's/\t/,\t/g;s/\$/\r/g' > ${filePath}.utf8
	echo "export  csv done"

	echo "conver csv file utf-8 to gbk ,generate new file ${filePath}"
	iconv -f UTF-8 -t GBK ${filePath}.utf8 > ${filePath}
	echo "convert ut-8 to gbk done"
}


exportDB2_CSV
csv2MySQL  
MySQL2FinalCSV `dirname $0`/RepayRealtimeMyql2CSV.sql 			/tmp/cdc_realtime_repay.csv
MySQL2FinalCSV `dirname $0`/PayinRealtimeMyql2CSV.sql 			/tmp/cdc_realtime_payin.csv
MySQL2FinalCSV `dirname $0`/SuperNetBankComeRealtimeMyql2CSV.sql /tmp/cdc_realtime_come.csv
MySQL2FinalCSV `dirname $0`/SuperNetBankGoRealtimeMyql2CSV.sql 	/tmp/cdc_realtime_go.csv
MySQL2FinalCSV `dirname $0`/CounterRealtimeMyql2CSV.sql 		/tmp/cdc_realtime_counter.csv

