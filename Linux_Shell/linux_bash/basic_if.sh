#!/bin/bash

# this example used for Mac ,Info.plist file ,find the value of the key
file=Info.plist
key=CFBundleIconFile

keyRowNo=`cat ${file}  | grep -n ${key} |cut -d : -f1`
valueRow=`sed -n "$((keyRowNo+1))"p ${file}`
noHeader=${valueRow#*<string>}
value=${noHeader%%<*}
echo $value >anotherfile