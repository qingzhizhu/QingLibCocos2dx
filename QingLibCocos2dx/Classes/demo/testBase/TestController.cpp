//
//  TestController.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#include "TestController.h"
#include "test.h"
#include "TestBaseLayer.h"

#define LINE_SPACE          40

USING_NS_QING;


static TestBaseLayer* CreateTestScene(int index){
    CCDirector::sharedDirector()->purgeCachedData();
    
    TestBaseLayer* layer = NULL;
    switch (index) {
        case TESTS_MYDEMO:
            layer = TestMyDemo::create();
            break;
        case TESTS_FONT:
            layer = TestFontDemo::create();
            break;
        case TESTS_MYMANAGER:
            layer = MyAssetsManagerDemo::create();
            break;
            
        case TESTS_LUA:
            layer = TestLuaDemo::create();
            break;
            
        case TESTS_LAYER:
            layer = TestLayerDemo::create();
            break;
        case TESTS_SPRITE:
            layer = TestSpriteDemo::create();
            break;
        case TESTS_CLIPPINGNODE:
            layer = TestClippingNodeDemo::create();
            break;
        case TESTS_UTILS_STORAGE:
            layer = StorageUtilsTest::create();
            break;
            
        default:
            break;
    }
    
    return layer;
}



//---------------
static CCPoint s_tCurPos = CCPointZero;


bool TestController::init()
{
    bool bRet = false;
    do
    {
//        CCDirector * pDirector;
//        CC_BREAK_IF(!(pDirector = CCDirector::sharedDirector()));
//        this->setContentSize(pDirector->getWinSize());
        m_bTouchEnabled = true;
        m_bAccelerometerEnabled = false;
        // success
        bRet = true;
    } while(0);
    return bRet;
}

TestController::TestController()
: m_tBeginPos(0, 0)
, m_pItemMenu(NULL)
{
	// add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathClose, s_pPathCloseSelected, this, menu_selector(TestController::closeCallback));
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    pCloseItem->setPosition(ccp(VisibleRect::right().x - 30 , VisibleRect::top().y - 30));
    addChild(pMenu, 1);
    
    //add menu ites for tests
    m_pItemMenu = CCMenu::create();
    for (int i=0; i < TESTS_COUNT; i++) {        
        //add the menu item for back to main menu
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
        //CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
        //#else
        CCLabelTTF* label = CCLabelTTF::create(g_aTestNames[i].c_str(), "Arial", 24);
        //#endif
        
        CCMenuItemLabel* pMenuItemLabel = CCMenuItemLabel::create(label, this, menu_selector(TestController::menuCallback));
        
        m_pItemMenu->addChild(pMenuItemLabel, 0, i + 10000);    
        pMenuItemLabel->setPosition(ccp(VisibleRect::center().x, (VisibleRect::top().y - (i+1) * LINE_SPACE )));
        
    }
    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (TESTS_COUNT + 1) * LINE_SPACE));
    m_pItemMenu->setPosition(s_tCurPos);
    addChild(m_pItemMenu);
    
    //这里有个坑，使用create方法，必须从写init方法，并且设置m_bTouchEnabled=true,从能滚动
    //若外部使用new的方式，这里设置true就可以滚动。
    setTouchEnabled(true);
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

void TestController::menuCallback(cocos2d::CCObject *pSender)
{
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getTag() - 10000;
    CCLOG("click menu index = %d", nIdx);
    // create the test scene and run it
    TestBaseLayer* layer = CreateTestScene(nIdx);
    if (layer)
    {
        layer->runThisLayer();
    }
    
}

//上一次手指的位置
void TestController::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    m_tBeginPos = touch->getLocation();
    
}

void TestController::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(m_pItemMenu->getContentSize().height < VisibleRect::getVisibleRect().size.height){
        return;
    }
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - m_tBeginPos.y;
    
    CCPoint curPos = m_pItemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
    if(nextPos.y < 0.0f){
        m_pItemMenu->setPosition(CCPointZero);
        return;
    }
    
    if(nextPos.y > ((TESTS_COUNT+1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height)){
        m_pItemMenu->setPosition(ccp(0, ((TESTS_COUNT+1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    m_pItemMenu->setPosition(nextPos);
    m_tBeginPos = touchLocation;
    s_tCurPos = nextPos;
}


