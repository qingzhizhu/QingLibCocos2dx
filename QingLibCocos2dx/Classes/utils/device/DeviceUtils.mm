//
//  DeviceUtils.mm
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 7/31/14.
//
//

#include "DeviceUtils.h"
#import "Reachability.h"

NS_QING_BEGIN


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

DeviceUtils::~DeviceUtils() { }



// 检测WIFI是否连接
bool DeviceUtils::isWifiEnabled()
{
    return ([[Reachability reachabilityForLocalWiFi] currentReachabilityStatus] != NotReachable);
}

NSString* testPage = @"www.baidu.com";

float DeviceUtils::getBatteryLeve()
{
    [[UIDevice currentDevice] setBatteryMonitoringEnabled:YES];
    return [[UIDevice currentDevice] batteryLevel];
}

// 检测3G网络是否可用
bool DeviceUtils::is3GEnabled()
{
    return [[Reachability reachabilityForInternetConnection] isReachableViaWWAN];
}


NETSTATUS DeviceUtils::getNetStatusType()
{
    Reachability *r = [Reachability reachabilityWithHostname:testPage];
    switch ([r currentReachabilityStatus]) {
        case NotReachable:
            // 没有网络连接
            return NETSTATUS_NONE;
            break;
        case ReachableViaWWAN:
            // 使用3G网络
            return NETSTATUS_3G;
            break;
        case ReachableViaWiFi:
            // 使用WiFi网络
            return NETSTATUS_WIFI;
            break;
    }
    return NETSTATUS_NONE;
}



NS_QING_END