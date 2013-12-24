//
//  TestDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-23.
//
//
/// 用来测试宏定义

#ifndef QingLibCocos2dx_TestDemo_h
#define QingLibCocos2dx_TestDemo_h

#include "Common.h"

//namespace QingCocos2dx {
NS_QING_BEGIN


class TestDemo : public CCNode
{
public:
    TestDemo();
    CREATE_FUNC(TestDemo);
    ~TestDemo();
    virtual void onEnter();
    

};

//}
NS_QING_END

#endif
