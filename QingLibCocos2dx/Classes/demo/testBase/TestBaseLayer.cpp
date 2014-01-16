//
//  TestBaseLayer.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#include "TestBaseLayer.h"
#include "TestController.h"

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
    
}

TestBaseLayer::~TestBaseLayer()
{
    
}


void TestBaseLayer::onEnter()
{
    CCLayer::onEnter();
    
    //add the menu item for back to main menu
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    //    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
    //#else
    CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TestBaseLayer::MainMenuCallback));
    label->setColor(ccc3(0xCC, 0xCC, 0xCC));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}


void TestBaseLayer::runThisLayer()
{
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    scene->removeAllChildren();
    scene->addChild(this);
}

//{
//    CCScene* s = new TestScene();
//    s->addChild( layer () );
//    CCDirector::sharedDirector()->replaceScene(s);
//    s->release();
//}


void TestBaseLayer::MainMenuCallback(cocos2d::CCObject *pSender)
{
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    scene->removeAllChildren();
    scene->addChild(TestController::create());
}
