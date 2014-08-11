//
//  DeviceUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 7/31/14.
//
//

//使用预编译，对当前平台为Android时才会导入如下头文件

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#include "DeviceUtils.h"

NS_QING_BEGIN

#define JAVA_CLS_DEVICE "com/qingzhizhu/ext/DeviceHelper"


static DeviceUtils *s_shared = NULL;

DeviceUtils * DeviceUtils::shared()
{
    if(!s_shared){
        s_shared = new DeviceUtils();
    }
    return s_shared;
}

void DeviceUtils::purge()
{
    CC_SAFE_RELEASE_NULL(s_shared);
}

DeviceUtils::DeviceUtils() { }

DeviceUtils::~DeviceUtils(){ }


bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
{
    bool b = JniHelper::getStaticMethodInfo(methodinfo, className, methodName, paramCode);
    if(!b){
        CCLog("[DeviceUtils] JNI 未找到java的函数 %s", methodName);
    }
    return b;
}



float DeviceUtils::getBatteryLeve()
{
    CCLog("Android 未实现 获取电量");
    return -1;
}

bool DeviceUtils::isWifiEnabled()
{
    JniMethodInfo minfo;
    bool isHave = getStaticMethodInfo(minfo, JAVA_CLS_DEVICE, "isWifiEnabled", "()Z");
    if(!isHave){
        return false;
    }
    jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
    
    CCLog("wifiEnabled: %d", ret);
    minfo.env->DeleteLocalRef(minfo.classID);
    if(ret){
        return true;
    }
    return false;
}

bool DeviceUtils::is3GEnabled()
{
    NETSTATUS ret = getNetStatusType();
    return ret == NETSTATUS_3G;
}


NETSTATUS DeviceUtils::getNetStatusType()
{
    JniMethodInfo minfo;
    bool isHave = getStaticMethodInfo(minfo, JAVA_CLS_DEVICE, "getNetWorkType", "()I");
    if(!isHave){
        return NETSTATUS_NONE;
    }
    int ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
    
    if(ret < NETSTATUS_NONE || ret >= NETSTATUS_MAX){
        return NETSTATUS_NONE;
    }
    CCLOG("[DeviceUtils] 使用的网络type=%d", ret);
    return NETSTATUS(ret);
}

bool BADevice::removeDir(string pathStr)
{
    int code = -1;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    string command = "rm -r ";
    // Path may include space.
    command += "\"" + pathStr + "\"";
    code = system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + pathStr + "\"";
    code = system(command.c_str());
#endif
    CCLog("[Device] system: %s ; code: %d", command.c_str(), code);
    return code == 0;
}

NS_QING_END