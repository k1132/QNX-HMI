#!/bin/sh

CMD="$1"

if [ $CMD == "start" ];then
    #echo "app start"
    display_image -zorder=2 -noinit=1 -display=1 -size=1200x1920 -file=/extra/Hinge_Apps/boot_animation/images/loading.png &
    echo "app::start" >> /pps/hinge-tech/application_status
    /extra/Hinge_Apps/qtcar/scripts/setappzorder.sh &
else
    echo "app::stop" >> /pps/hinge-tech/application_status
    pid=`pidin ar | grep loading | grep -v grep | awk '{if($2=="display_image"){print $1}}'`
    if [ -n "$pid" ]; then
        slay -f $pid &
        #echo "app stop"
        echo "msg::stop\ndat::\nid::1" > /pps/services/launcher/control
        /extra/Hinge_Apps/qtcar/scripts/appslay.sh &
    fi
fi

exit 0;
