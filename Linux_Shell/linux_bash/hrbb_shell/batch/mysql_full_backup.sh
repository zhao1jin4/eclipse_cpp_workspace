#!/usr/bin/bash

now=`date +"%Y-%m-%d_%H:%M:%S"`
mysqldump -h35.8.33.11 -ucdcquery -pcdcquery  --opt --default-character-set=utf8  --extended-insert=false --complete-insert=true --single-transaction  --databases  cdcquery  > cdcquery_full_backup_${now}.sql 
