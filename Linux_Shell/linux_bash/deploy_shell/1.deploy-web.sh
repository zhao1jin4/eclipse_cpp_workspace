
today=`date +"%Y-%m-%d %H:%M:%S" `

echo "${today} DEPLOY WEB START   shutdown tomcat"
/opt/tomcat-web/bin/shutdown.sh
sleep 1
pid=`ps -ef |grep tomcat-web |grep -v 'grep'  | awk  -F ' '  '{print $2}'`

 if [ "$pid" != "" ]; then

        echo "kill ${pid}"
        kill ${pid}
        sleep 1

        echo "kill -9 ${pid}"
        kill -9 ${pid}


 else
       echo "no process  tomcat-web"
fi



rm -rf /opt/tomcat-web/webapps/*

cp /root/.jenkins/workspace/bugfix-08-op-manger/com-ycg-rosefinch-op-manager-web/target/op-manager.war /opt/tomcat-web/webapps/

echo "remote scp"

scp /root/.jenkins/workspace/bugfix-03-baseinfo-test/com-ycg-rosefinch-op-baseinfo-serviceLauncher/target/com-ycg-rosefinch-op-baseinfo-bin.zip  172.16.35.20:/home/app/op/com-ycg-rosefinch-op-baseinfo
scp /root/.jenkins/workspace/bugfix-04-route-test/com-ycg-rosefinch-op-route-serviceLauncher/target/com-ycg-rosefinch-op-route-bin.zip                   172.16.35.20:/home/app/op/com-ycg-rosefinch-op-route
scp /root/.jenkins/workspace/bugfix-06-op-api/com-ycg-rosefinch-op-api-serviceLauncher/target/com-ycg-rosefinch-op-api-bin.zip                                   172.16.35.20:/home/app/op/com-ycg-rosefinch-op-api

echo "deploy dubbo"
ssh  172.16.35.20  /home/zh/deploy-dubbo.sh

echo "start tomcat wating 30 seconds"
/opt/tomcat-web/bin/startup.sh &
sleep 30

echo "DONE--------"




