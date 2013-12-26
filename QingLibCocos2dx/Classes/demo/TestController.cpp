//
//  TestController.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#include "TestController.h"
#include "test.h"
#include "VisibleRect.h"


USING_NS_QING;


TestController::TestController()
: m_tBeginPos(0, 0)
, m_pItemMenu(NULL)
{
	// add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathClose, s_pPathClose, this, menu_selector(TestController::closeCallback));
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    pCloseItem->setPosition(ccp(VisibleRect::right().x - 30 , VisibleRect::top().y - 30));
    addChild(pMenu, 1);
    
    
}

TestController::~TestController()
{
	// TODO: auto generated code
}

void TestController::closeCallback(cocos2d::CCObject *pSender)
{
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


