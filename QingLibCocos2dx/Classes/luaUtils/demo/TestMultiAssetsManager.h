//
//  TestMultiAssetsManager.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-25.
//
//
/// 测试的基类layer

#ifndef __QingLibCocos2dx__TestMultiAssetsManager__
#define __QingLibCocos2dx__TestMultiAssetsManager__

#include "Common.h"
#include "TestBaseLayer.h"

NS_QING_BEGIN


class TestMultiAssetsManager : public TestBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(TestMultiAssetsManager);
    TestMultiAssetsManager();
	~TestMultiAssetsManager();
	
	virtual void onEnter();
	virtual void onExit();
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestMultiAssetsManager__) */
