//
//  TestDeviceInfoDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 7/31/14.
//
//

#include "TestDeviceInfoDemo.h"
#include "DeviceUtils.h"

NS_QING_BEGIN

bool TestDeviceInfoDemo::init()
{
	bool bRet = false;
	do
	{
	    m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestDeviceInfoDemo::TestDeviceInfoDemo()
{
	// TODO: auto generated code
}

TestDeviceInfoDemo::~TestDeviceInfoDemo()
{
	// TODO: auto generated code
}

CCLayer* TestDeviceInfoDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
	// TODO: auto generated code
	switch (m_nLayerIndex) {
        case 0:{
            setTitle("正在使用的网络类型");
            
            string str = "IOS:";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            str = "Android:";
#endif
            NETSTATUS type = DeviceUtils::shared()->getNetStatusType();
            switch (type) {
                case NETSTATUS_NONE:
                    str += "没使用任何网络！";
                    break;
                case NETSTATUS_3G:
                    str += "使用 3G 网络！";
                    break;
                case NETSTATUS_WIFI:
                    str += "使用 WIFI 网络！";
                    break;
                case NETSTATUS_2G:
                    str += "使用 2G 网络！";
                    break;
                case NETSTATUS_2G_WAP:
                    str += "使用 2G WAP 网络！";
                    break;
                    
                default:
                    break;
            }
            createLabel(layer, str);
        }
            break;
            
        case 1:{
            setTitle("正在连接WIFI吗？");
            
            string str = "IOS:";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
      str = "Android:";
#endif
            if(DeviceUtils::shared()->isWifiEnabled()){
                str += "在链接wifi";
            }else{
                str += "没有链接！ ";
            }
            createLabel(layer, str);
        }
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

NS_QING_END