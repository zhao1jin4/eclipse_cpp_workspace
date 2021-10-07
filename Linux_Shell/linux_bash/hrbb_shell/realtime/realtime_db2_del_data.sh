#!/bin/bash

db2User=db2inst1
db2Pass=db2inst1
db2Alias=db2inst1
#db2Host=35.8.33.25

now=`date +"%Y-%m-%d %H:%M:%S"`
echo "==${now}== start cron job === "


echo " ----------begin connect to db2  "
#db2 connect to ${db2Alias} user ${db2User} using ${db2Pass}
. ~/sqllib/db2profile
~/sqllib/bin/db2 connect to  cdcquery
~/sqllib/bin/db2 <<EOF

	!echo " -------begin delete db2 table pubtrandef sysdate 5 days ago"
	delete from pubtrandef   where  modifytime <  current date - 5 days
	
	!echo " -------begin delete db2 table pubtranext sysdate 5 days ago"
	delete from pubtranext   where  modifytime < current date - 5 days
	
	!echo " -------begin delete db2 table tbl_bfrocred  updateTime 5 days ago"
	delete from tbl_bfrocred where modifytime < current date - 5 days
	
	!echo " -------begin delete db2 table tbl_bcomecred  updateTime 5 days ago"
	delete from tbl_bcomecred where modifytime < current date - 5 days
	
	!echo " -------begin delete db2 table tbl_glssubtranslog trandate 5 days ago"
	delete from glssubtranslog where modifytime <  current date - 2 days
	commit
	
	connect reset
	quit
EOF
echo " ----------delete db2 table 5 days ago  done  "
 