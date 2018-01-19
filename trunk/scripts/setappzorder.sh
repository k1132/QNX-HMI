apk="`pidin ar | grep "r 270" | grep -v grep | awk '{print $2}'`"
if [ -n "$apk" ];then
  /extra/Hinge_Apps/qtcar/scripts/setzorder.sh $apk 2
fi
exit 0;
