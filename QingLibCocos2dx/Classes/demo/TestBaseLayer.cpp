//
//  TestBaseLayer.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#include "TestBaseLayer.h"

USING_NS_QING;

bool TestBaseLayer::init()
{
	bool bRet = false;
	do
	{
		// TODO: auto generated code
//        CCLayer.init()实现体，开启滚动用 m_bTouchEnabled = true;
//        CCDirector * pDirector;
//        CC_BREAK_IF(!(pDirector = CCDirector::sharedDirector()));
//        this->setContentSize(pDirector->getWinSize());
        m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestBaseLayer::TestBaseLayer()
{
	// TODO: auto generated code
}

TestBaseLayer::~TestBaseLayer()
{
	// TODO: auto generated code
}

