#!/bin/bash
# @author Kevin Geng

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "DIR=$DIR"
APPNAME="QingLibCocos2dx"

date_start="$(date +%s)"

# c++ headers.
cd $DIR/jni/
sh mksrc.sh

# compile c++.
cd $DIR
sh $DIR/build_native.sh

date_end="$(date +%s)"
diff=$[date_end - date_start]
echo "\nCompile C++ files use time: `echo $diff/60|bc` Mins, `echo $diff%60|bc` Secs.\n"

# package apk.
ant release

# install & start apk.
ant installr
adb shell am start -n com.qingzhizhu.cocos2dx/com.qingzhizhu.cocos2dx.QingLibCocos2dx

date_end="$(date +%s)"
diff=$[date_end - date_start]
echo "Run Successful! Use total time: `echo $diff/60|bc` Mins, `echo $diff%60|bc` Secs."

# paly sound.
#afplay -t 10 $DIR/../$APPNAME/Mp3Sounds/airfield_click.mp3

# mac notification
osascript -e 'display notification "已安装并启动！" with title "看手机" sound name "Sosumi"'

