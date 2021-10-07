#!/usr/bin/bash
for path in `ls /home/hrbfex/file/CDC/CBS_PUBTRANDEF_*.dat` ;do
	filename=${path##*/}
	theDay=$(filename:15:(8))
	./batch_mysql_cs.sh $theDay
done