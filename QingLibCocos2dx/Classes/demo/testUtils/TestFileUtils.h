//
//  TestFileUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-5.
//
//
/// 测试的基类layer

#ifndef __QingLibCocos2dx__TestFileUtils__
#define __QingLibCocos2dx__TestFileUtils__

#include "Common.h"
#include "TestBaseLayer.h"

NS_QING_BEGIN


class TestFileUtils : public TestBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(TestFileUtils);
    TestFileUtils();
	~TestFileUtils();
	
	virtual void onEnter();
	virtual void onExit();
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestFileUtils__) */
