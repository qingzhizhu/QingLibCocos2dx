//
//  QingSprite.h
//  QingLibCocos2dxLua
//
//  Created by Kevin Geng on 14-3-13.
//
//
/// 测试lua调用自定义类

#ifndef __QingLibCocos2dxLua__QingSprite__
#define __QingLibCocos2dxLua__QingSprite__

#include "Common.h"

NS_QING_BEGIN


class QingSprite : public CCSprite
{
public:
    static QingSprite* createQingSprite(const char* _name);
    void sayHello(const char* str);
};

NS_QING_END

#endif /* defined(__QingLibCocos2dxLua__QingSprite__) */
