//
//  TestDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-23.
//
//

#include "TestDemo.h"
#include "TestBaseObject.h"

//using namespace QingCocos2dx;
USING_NS_QING;

//下面的和上面的效果相同。
//NS_QING_BEGIN

TestDemo::TestDemo()
{
    CCLOG("TestDemo construct");
}

TestDemo::~TestDemo()
{
    CCLOG("TestDemo de construct");
}


void TestDemo::onEnter()
{
    CCLOG("onEnter");
    this->setPosition(ccp(10, 290));
    
}


//NS_QING_END
