//
//  DeviceUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 7/31/14.
//
//
/// 继承BaseObject.
/// 获取手机的一些信息，cpp 不参与Xcode 编译

#ifndef __QingLibCocos2dx__DeviceUtils__
#define __QingLibCocos2dx__DeviceUtils__

#include "Common.h"

NS_QING_BEGIN


enum NETSTATUS
{
    // Apple NetworkStatus Compatible Names.
    NETSTATUS_NONE   = 0,
    NETSTATUS_3G     = 1,   //使用3G/GPRS网络
    /** wifi网络 */
    NETSTATUS_WIFI   = 2,
    //---------- android 用 ----------------
    /** 2G网络 */
    NETSTATUS_2G     = 3,
    /** WAP网络 区分2G网络是为wap，还是net,类型，因为wap类型，需要配置代理上网 */
    NETSTATUS_2G_WAP = 4,
    
    NETSTATUS_MAX
};


class DeviceUtils : public BaseObject
{
public:
    
    static DeviceUtils * shared();
    void purge();
    
    
    
    // 获取电池电量，范围0到1.0。－1表示电量未知。
    float getBatteryLeve();
    
    /**
	 * 检测WIFI是否可用
	 * @return
	 */
    bool isWifiEnabled();
    
    /** 检测3G网络是否可用 */
    bool is3GEnabled();
    
    /** 取得网络连接状况 */
    NETSTATUS getNetStatusType();
    
    
    /**删除文件夹*/
    bool removeDir(string path);
    
    
protected:

    
private:
    DeviceUtils();
	DeviceUtils(const DeviceUtils &);
    DeviceUtils &operator=(const DeviceUtils &);
    ~DeviceUtils();
    
    
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__DeviceUtils__) */
