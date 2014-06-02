//
//  StorageUtilsTest.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-2.
//
//
/// 测试的基类layer

#ifndef __QingLibCocos2dx__StorageUtilsTest__
#define __QingLibCocos2dx__StorageUtilsTest__

#include "Common.h"
#include "TestBaseLayer.h"

NS_QING_BEGIN


class StorageUtilsTest : public TestBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(StorageUtilsTest);
    StorageUtilsTest();
	~StorageUtilsTest();
	
	virtual void onEnter();
	virtual void onExit();
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__StorageUtilsTest__) */
