//
//  TestJsonDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-9-29.
//
//
/// 底部带回退，重置，前进按钮

#ifndef __QingLibCocos2dx__TestJsonDemo__
#define __QingLibCocos2dx__TestJsonDemo__

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN


class TestJsonDemo : public TestBaseDemo
{
public:
	virtual bool init();
	CREATE_FUNC(TestJsonDemo);
	TestJsonDemo();
	virtual ~TestJsonDemo();

	/**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 1; }
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestJsonDemo__) */
