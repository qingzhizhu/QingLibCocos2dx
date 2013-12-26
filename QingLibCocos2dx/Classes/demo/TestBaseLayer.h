//
//  TestBaseLayer.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#ifndef __QingLibCocos2dx__TestBaseLayer__
#define __QingLibCocos2dx__TestBaseLayer__

#include "Common.h"

NS_QING_BEGIN


class TestBaseLayer : public CCNode
{
public:
	virtual bool init();
	CREATE_FUNC(TestBaseLayer);
	TestBaseLayer();
	virtual ~TestBaseLayer();

};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestBaseLayer__) */
