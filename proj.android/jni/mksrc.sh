#!/bin/bash

echo 'LOCAL_SRC_FILES := hellocpp/main.cpp \' > Sources.mk
#find ../../QingLibCocos2dx/libs/LibJson -name "*.cpp"|awk '{print $1,"\\"}' >> Sources.mk
find ../../QingLibCocos2dx/Classes -name "*.cpp"|awk '{print $1,"\\"}' >> Sources.mk
echo >> Sources.mk

echo 'LOCAL_C_INCLUDES := \' >Includes.mk
#find ../../QingLibCocos2dx/libs/LibJson -type d -not -wholename '*.svn*'|awk '{printf "$(LOCAL_PATH)/%s \\\n",$1}' >> Includes.mk
find ../../QingLibCocos2dx/Classes -type d -not -wholename '*.svn*'|awk '{printf "$(LOCAL_PATH)/%s \\\n",$1}' >> Includes.mk
echo >> Includes.mk
