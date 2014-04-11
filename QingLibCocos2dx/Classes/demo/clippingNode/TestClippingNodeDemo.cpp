//
//  TestClippingNodeDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-4-11.
//
//

#include "TestClippingNodeDemo.h"
#include "test.h"


USING_NS_QING;

bool TestClippingNodeDemo::init()
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

TestClippingNodeDemo::TestClippingNodeDemo()
: m_pRect(NULL)
, m_pImgTip(NULL)
, m_pClip(NULL)
{
	// TODO: auto generated code
}

TestClippingNodeDemo::~TestClippingNodeDemo()
{
	// TODO: auto generated code
}

CCLayer* TestClippingNodeDemo::getLayerByIndex()
{
    this->unscheduleUpdate();
	CCLayer * layer = CCLayer::create();

	switch (m_nLayerIndex) {
        case 0:{
            setTitle("遮罩2-ClippingNode 使用cocos2dx建立的默认工程，\n是不开启Stencil Buffer的，需要自己手动开启；\n开启办法：打开AppController.mm，将初始化EAGLView的\n代码里的GL_DEPTH_COMPONENT16改成GL_DEPTH24_STENCIL8_OES即可。  ");
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            CCSprite *loadingBar = CCSprite::create(s_pPathLoadingBar);
            CCSize lbsz;
            if(loadingBar)
            {
                lbsz = loadingBar->getContentSize();
                loadingBar->setPosition(ccp(size.width/2,lbsz.height/1.85 - 2 + 30));
                layer->addChild(loadingBar, 10);
            }
            
            CCSprite* m_loadingProgress = CCSprite::create(s_pPathLoadingProgress);
            if(m_loadingProgress)
            {
                CCSize lpsz = m_loadingProgress->getContentSize();
                m_loadingProgress->setAnchorPoint(ccp(0,0.5));
                m_loadingProgress->setPosition(ccp((size.width-lpsz.width)/2,lbsz.height/1.85 - 2 + 30));
                
                
                CCClippingNode* m_pClip = CCClippingNode::create();
                m_pClip->setContentSize(lpsz);
                
                
                CCPoint lpps = m_loadingProgress->getPosition();
                CCLayerColor* rect = CCLayerColor::create(ccc4(0xFF,0,0,80), lpsz.width, lpsz.height);
                rect->ignoreAnchorPointForPosition(false);
                rect->setAnchorPoint(ccp(0, 0.5));
                rect->setPosition(lpps);
                
                m_pClip->setStencil(rect);
                m_pClip->addChild(m_loadingProgress);
                layer->addChild(m_pClip, 10);
                rect->setScaleX(0.0);
                
                m_pClip->setInverted(false);
                //                m_pClip->setAlphaThreshold(0.0f);
                
                this->scheduleUpdate();
                
                this->m_pRect = rect;
                
                CCSprite* img = CCSprite::create(s_pPathHelloWorldp);
                img->setPosition(VisibleRect::center());
                layer->addChild(img);
                CCClippingNode* clip2 = CCClippingNode::create();
                //向裁剪节点中加入内容，这里加入的是一个透明的层
                clip2->addChild(CCLayerColor::create(ccc4(0,0,0, 200)));
                //向裁剪节点中加入精灵，精灵的位置和裁剪的位置相同，所以最后让裁剪掉了
                img = CCSprite::create(s_pPathSoldier1);
                img->setPosition(VisibleRect::center());
                clip2->addChild(img);
                //创建模板，裁剪节点将按照这个模板来裁剪区域
                img = CCSprite::create(s_pPathSoldier1);
                img->setPosition(VisibleRect::center());
                clip2->setStencil(img);
                //这个是用来设置显示裁剪区域还是非裁剪区域的
                clip2->setInverted(true);
                //我们之前放了一张裁剪的模板，按照这个模板裁剪的时候同时按照这个alpha的值裁剪，这个值的范围是0-137
                //设为0就把透明的区域裁剪掉
                clip2->setAlphaThreshold(0.0f);
                layer->addChild(clip2);
            }
        }
            break;
            
        case 1:{
            setTitle("ClippingNode 做新手引导");
            CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();
            
            CCSprite* background = CCSprite::create(s_pPathHelloWorldp);//创建背景
            background->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
            layer->addChild(background,0);
            
            CCClippingNode* clip=CCClippingNode::create();//创建裁剪节点，成员变量
            clip->setInverted(true);//设置底板可见
            clip->setAlphaThreshold(0.0f);//设置alpha为0
            
            
            CCLayerColor* back=CCLayerColor::create(ccc4(0,0,0,200));
            clip->addChild(back);//为裁剪节点添加一个黑色带透明（看起了是灰色）的底板
            
            //模版如果要在其他地方使用要记得retain！
            
            //第一种：以下模型是drawnode遮罩
            //CCDrawNode* front=CCDrawNode::create();
            //ccColor4F yellow = {1, 1, 0, 1};
            //CCPoint rect[4]={ccp(-30,30),ccp(30,30),ccp(30,-30),ccp(-30,-30)};
            //front->drawPolygon(rect, 4, yellow, 0, yellow);
            //front->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
            //clip->setStencil(front);
            
            //第二种：以下模型是带图像遮罩
            CCNode* nodef=CCNode::create();//创建模版
            CCSprite* close=CCSprite::create(s_pPathClose);//这里使用的是close的那个图标，所以注意观察效果图2
            nodef->addChild(close);//在模版上添加精灵
            nodef->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
            clip->setStencil(nodef);//设置模版
            layer->addChild(clip,1);//添加裁剪节点
            m_pClip = clip;
            
            CCSprite* tip = CCSprite::create(s_pPathTip1);//一些引导提示
            tip->setScale(0.5f);
            tip->setRotation(60);
            tip->setPosition(ccp(visibleSize.width/2-70,visibleSize.height/2+50));
            layer->addChild(tip,2);
            
            tip->runAction(CCRepeatForever::create(CCSequence::create(CCScaleBy::create(0.25f,0.95f),CCScaleTo::create(0.25f,0.5),NULL)));
            m_pImgTip = tip;
            
            this->setTouchEnabled(true);//触摸有效，落点正确时移除裁剪节点和提示，相关处理请看源码
            
        }
            
            break;
            
		default:
            break;
    }
            
	
	return layer;
}



void TestClippingNodeDemo::update(float delta)
{
    TestBaseDemo::update(delta);
    if(m_pRect){
        float s = m_pRect->getScaleX() + .01;
        if(s > 1){
            s = 0;
        }
        m_pRect->setScaleX(s);
    }
}

void TestClippingNodeDemo::registerWithTouchDispatcher()
{
	CCDirector *pDirector=CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}


bool TestClippingNodeDemo::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_pClip == NULL) return false;
    CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();
    CCLOG("clippingnode = (%f,%f)", m_pClip->getContentSize().width, m_pClip->getContentSize().height);
	CCPoint point=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	CCRect rect=CCRectMake(visibleSize.width/2-30,visibleSize.height/2-30,60,60);
	if (rect.containsPoint(point))
	{
        if(m_pClip) m_pClip->removeFromParent();
        if(m_pImgTip) m_pImgTip->removeFromParent();
        m_pClip = NULL;
        m_pImgTip = NULL;
		return true;
	}
	return false;
}
