//
//  TestNetworkDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-28.
//
//
/// 底部带回退，重置，前进按钮
/// 有关网络的请求demo

#ifndef __QingLibCocos2dx__TestNetworkDemo__
#define __QingLibCocos2dx__TestNetworkDemo__

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN


class TestNetworkDemo : public TestBaseDemo
{
public:
	virtual bool init();
	CREATE_FUNC(TestNetworkDemo);
	TestNetworkDemo();
	virtual ~TestNetworkDemo();

	/**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 1; }
    
    
    
    
    
    friend int onProgress(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded);
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestNetworkDemo__) */
