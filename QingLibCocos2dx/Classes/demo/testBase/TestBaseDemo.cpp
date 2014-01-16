//
//  TestBaseDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-1-16.
//
//

#include "TestBaseDemo.h"
#include "test.h"

USING_NS_QING;


TestBaseDemo::TestBaseDemo()
: m_pContainer(NULL)
, m_nLayerIndex(0)
{
    addBottomUI();
    
    //init container
    m_pContainer = CCNode::create();
    addChild(m_pContainer, 0);
    
    
}

TestBaseDemo::~TestBaseDemo()
{
    
}



void TestBaseDemo::addBottomUI()
{
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(TestBaseDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(TestBaseDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(TestBaseDemo::nextCallback) );
    
    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);
    
    menu->setPosition( CCPointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));;
    
    addChild(menu, 1);
}

void TestBaseDemo::backCallback()
{
    CCLOG("[TestBaseDemo] callback");
    m_nLayerIndex --;
    addDemoLayer();
}

void TestBaseDemo::restartCallback()
{
    CCLOG("[TestBaseDemo] restart call ");
    addDemoLayer();
}


void TestBaseDemo::nextCallback()
{
    CCLOG("[TestBaseDemo] next call");
    m_nLayerIndex ++;
    addDemoLayer();
}

void TestBaseDemo::addDemoLayer()
{
    m_nLayerIndex = m_nLayerIndex < 0 ? getLayerLen()-1 : m_nLayerIndex;
    m_nLayerIndex = m_nLayerIndex >= getLayerLen() ? 0 : m_nLayerIndex;
    
    m_pContainer->removeAllChildren();
    CCLayer* layer = getLayerByIndex();
    if(layer){
        m_pContainer->addChild(layer);
    }else{
        CCLOG("[TestBaseDemo] index = %d, layer is NULL!", m_nLayerIndex);
    }
}


void TestBaseDemo::onEnter()
{
    TestBaseLayer::onEnter();
    addDemoLayer();
}

