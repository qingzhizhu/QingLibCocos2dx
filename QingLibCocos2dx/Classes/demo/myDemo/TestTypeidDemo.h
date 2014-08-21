//
//  TestTypeidDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 8/20/14.
//
//
/// 底部带回退，重置，前进按钮
/// typeid 和 dynamic_cast

#ifndef __QingLibCocos2dx__TestTypeidDemo__
#define __QingLibCocos2dx__TestTypeidDemo__

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN


class TestTypeidDemo : public TestBaseDemo
{
public:
	virtual bool init();
	CREATE_FUNC(TestTypeidDemo);
	TestTypeidDemo();
	virtual ~TestTypeidDemo();

	/**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 3; }
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestTypeidDemo__) */
