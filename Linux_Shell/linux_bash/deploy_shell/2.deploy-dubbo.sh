

today=`date +"%Y-%m-%d %H:%M:%S" `
echo "${today} DEPLOY DUBBO   SATRT"

function  killProc()
{
        name=$1

        pid=`ps -ef |grep $name |grep -v 'grep'  | awk  -F ' '  '{print $2}'`
        if [ "$pid" != "" ]; then
                echo "kill ${name} ${pid}"
                kill ${pid}
         else
                echo "no process  ${name}"
        fi

}
killProc op-baseinfo
killProc op-route
killProc op-api



echo "STARTING op-baseinfo"
cd /home/app/op/com-ycg-rosefinch-op-baseinfo
echo "DELETE query"
rm -rf query
unzip  com-ycg-rosefinch-op-baseinfo-bin.zip
cd query
nohup /usr/local/jdk/bin/java -jar com-ycg-rosefinch-op-baseinfo.jar  >nohup.out &
sleep 9




echo "STARTING op-route"
cd /home/app/op/com-ycg-rosefinch-op-route
echo "DELETE query"
rm -rf query
unzip com-ycg-rosefinch-op-route-bin.zip
cd query
nohup /usr/local/jdk/bin/java -jar com-ycg-rosefinch-op-route.jar >nohup.out &
sleep 5



echo "STARTING op-api"
cd /home/app/op/com-ycg-rosefinch-op-api
echo "DELETE query"
rm -rf query
unzip com-ycg-rosefinch-op-api-bin.zip
cd query
nohup /usr/local/jdk/bin/java -jar com-ycg-rosefinch-op-api.jar >nohup.out &
sleep 8
echo "${today} DEPLOY DUBBO    DONE"



# vi  /home/app/op/com-ycg-rosefinch-op-baseinfo/query/nohup.out
# vi /home/app/op/com-ycg-rosefinch-op-route/query/nohup.out
#  vi  /home/app/op/com-ycg-rosefinch-op-api/query/nohup.out







