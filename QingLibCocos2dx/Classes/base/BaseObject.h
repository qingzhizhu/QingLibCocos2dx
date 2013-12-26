//
//  BaseObject.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//
/// 此类的目的在于与cocos2dx 无缝连接，便于扩展。
/// 项目的其他类等继承这个类。

#ifndef __QingLibCocos2dx__BaseObject__
#define __QingLibCocos2dx__BaseObject__

#include "Common.h"

NS_QING_BEGIN


class BaseObject : public CCObject
{
public:
    BaseObject();
	~BaseObject();
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__BaseObject__) */
