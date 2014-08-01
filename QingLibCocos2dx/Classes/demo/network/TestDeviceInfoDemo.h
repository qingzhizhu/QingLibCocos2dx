//
//  TestDeviceInfoDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 7/31/14.
//
//
/// 底部带回退，重置，前进按钮

#ifndef __QingLibCocos2dx__TestDeviceInfoDemo__
#define __QingLibCocos2dx__TestDeviceInfoDemo__

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN


class TestDeviceInfoDemo : public TestBaseDemo
{
public:
	virtual bool init();
	CREATE_FUNC(TestDeviceInfoDemo);
	TestDeviceInfoDemo();
	virtual ~TestDeviceInfoDemo();

	/**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 2; }
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestDeviceInfoDemo__) */
