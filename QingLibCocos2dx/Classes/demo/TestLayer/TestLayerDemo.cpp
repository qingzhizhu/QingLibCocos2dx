//
//  TestLayerDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-4-4.
//
//

#include "TestLayerDemo.h"

USING_NS_QING;

bool TestLayerDemo::init()
{
	bool bRet = false;
	do
	{
        m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestLayerDemo::TestLayerDemo()
{
	// TODO: auto generated code
}

TestLayerDemo::~TestLayerDemo()
{
	// TODO: auto generated code
}

CCLayer* TestLayerDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
	switch (m_nLayerIndex) {
        case 0:{
            setTitle("渐变层");
            CCSize size = CCSizeMake(80, 80);
            CCLayerGradient* lay1 = CCLayerGradient::create(ccc4(255, 0, 0, 255), ccc4(255, 0, 255, 255));
            lay1->setContentSize(size);
            lay1->setPosition(50, 50);
            layer->addChild(lay1);
            
            CCLayerGradient* lay2 = CCLayerGradient::create(ccc4(0, 0, 0, 127), ccc4(255, 255, 255, 127));
            lay2->setContentSize(size);
            lay2->setPosition(100, 90);
            layer->addChild(lay2);
            
            CCLayerGradient* lay3 = CCLayerGradient::create();
            lay3->setContentSize(size);
            lay3->setPosition(150, 140);
            lay3->setStartColor(ccc3(255, 0, 0));
            lay3->setEndColor(ccc3(255, 0 , 255));
            lay3->setStartOpacity(255);
            lay3->setEndOpacity(255);
            
            ccBlendFunc blend;
            blend.src = GL_SRC_ALPHA;
            blend.dst = GL_ONE_MINUS_SRC_ALPHA;
            lay3->setBlendFunc(blend);
            
            layer->addChild(lay3);
            this->unscheduleUpdate();
            this->scheduleUpdate();
        }
            break;
            
        case 1:{
            setTitle("图片的坐标");
            layer->setPositionX(10);
            this->unscheduleUpdate();
            CCSprite* img = CCSprite::create("Icon.png");
            img->setAnchorPoint(CCPointZero);
            img->cocos2d::CCNode::setPosition(20, 40);
            layer->addChild(img);
            CCLOG("img wid=%f, hei=%f, ", img->getContentSize().width, img->getContentSize().height);
            
            CCMoveTo* to = CCMoveTo::create(0.5, ccp(100, 40));
            img->runAction(to);
            
            
            CCSprite* img2 = CCSprite::create("Icon.png");
            img2->setAnchorPoint(ccp(1, 1));
            img2->cocos2d::CCNode::setPosition(5, -20);
            
            CCPoint p = img->convertToNodeSpace(img2->getPosition());
            CCLOG("img2 相对于 img1 位置 x = %f, y = %f. 相当于img的全局坐标减img2的全局坐标.", p.x, p.y);
            
            p = img->convertToWorldSpace(img2->getPosition());
            CCLOG("img2 相对于 img 坐标的位置 x = %f, y = %f. ", p.x, p.y);
            
//            p = img->convertToWorldSpace(CCPointZero);
//            CCLOG("img 左下角 相对于 world 位置 x = %f, y = %f.", p.x, p.y);
//            
//            p = img2->convertToWorldSpace(CCPointZero);
//            CCLOG("img2 左下角 world 位置 x = %f, y = %f.", p.x, p.y);
//            
//            p = img->convertToWorldSpace(img->getAnchorPointInPoints());
//            CCLOG("img 中心点 相对于 world 位置 x = %f, y = %f.", p.x, p.y);
//            
//            p = img2->convertToWorldSpace(img2->getAnchorPointInPoints());
//            CCLOG("img2 中心点 相对于  world 位置 x = %f, y = %f.", p.x, p.y);
            
            
        }
            
            break;
            
        default:
            break;
    }
	return layer;
}

void TestLayerDemo::update(float delta)
{
    CCNode::update(delta);
    CCLOG( "update %f", delta);
    
}

