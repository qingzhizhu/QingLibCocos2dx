//
//  TestSpriteDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-4-8.
//
//

#include "TestSpriteDemo.h"
#include "DisplayObjectUtils.h"


USING_NS_QING;

bool TestSpriteDemo::init()
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

TestSpriteDemo::TestSpriteDemo()

{
//	m_pContainer->setContentSize(CCDirector::sharedDirector()->getWinSize());
//    m_pContainer->setAnchorPoint(ccp(.5,.5));
    
}

TestSpriteDemo::~TestSpriteDemo()
{
	// TODO: auto generated code
}

CCLayer* TestSpriteDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
//    layer->setContentSize(CCDirector::sharedDirector()->getWinSize());
	switch (m_nLayerIndex) {
        case 0:{
//            layer->setAnchorPoint(ccp(.5,.5));
            CCSprite* img = CCSprite::create(s_pPathTexture1);
            CCLOG("[Anchor Point] this = (%f, %f)", this->getAnchorPoint().x, this->getAnchorPoint().y);
            CCLOG("[Anchor Point] contner = (%f, %f)", m_pContainer->getAnchorPoint().x, m_pContainer->getAnchorPoint().y);
            CCLOG("[Anchor Point] layer = (%f, %f)", layer->getAnchorPoint().x, layer->getAnchorPoint().y);
            CCLOG("[Anchor Point] img = (%f, %f)", img->getAnchorPoint().x, img->getAnchorPoint().y);
            setTitle("平铺， 文理的宽高必是2的n次方，如64*32...");
            img->setAnchorPoint(CCPointZero);
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            
            img->setTextureRect(CCRectMake(0, 0, size.width, size.height));
            ccTexParams  params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
            img->getTexture()->setTexParameters(&params);
            
            
            layer->addChild(img);
            
            
            img = CCSprite::create(s_pPathTexture1);
            DisplayObjectUtils::repeatImg(img, CCSizeMake(200, 300));
            img->setAnchorPoint(CCPointZero);
            img->setPositionX(20);
            layer->addChild(img);
            
            return layer;
            
            CCSize imgSize = img->getContentSize();
            int col = ceilf(size.width * 1.0 / imgSize.width);
            int raw = ceilf(size.height * 1.0 / imgSize.height);
            for (int i=0; i<col; i++) {
                for (int j=0; j<raw; j++) {
                    if(i == 0 && j == 0) continue;
                    img = CCSprite::create(s_pPathTexture1);
                    img->setAnchorPoint(CCPointZero);
                    img->cocos2d::CCNode::setPosition(imgSize.width * i, imgSize.height * j);
                    layer->addChild(img);
                }
            }
            
        }
            break;
            
        case 1:{
            setTitle("遮罩1-CCRenderTexture 性能较低，得到的文理Y轴是反的。参考ClippingNode 例子");
            CCSprite* img = CCSprite::create(s_pPathSoldier1);
            CCSprite* mask = CCSprite::create("Icon.png");
            CCPoint p = VisibleRect::leftTop();
            p.x += 100;
            p.y -= 100;
            img->setPosition(p);
            layer->addChild(img);
            p.x += mask->getContentSize().width + 20;
            p.y += mask->getContentSize().height;
            mask->setPosition(p);
            layer->addChild(mask);
            
            img = CCSprite::create(s_pPathSoldier1);
            mask = CCSprite::create("Icon.png");
            img->setAnchorPoint(CCPointZero);
            img->setPosition(CCPointZero);
            mask->setAnchorPoint(CCPointZero);
            mask->setPosition(CCPointZero);
            
            mask->setBlendFunc((ccBlendFunc){GL_ONE, GL_ZERO });
            ccBlendFunc blendFunc;
            blendFunc.src = GL_DST_ALPHA;   //表示使用目标颜色的alpha值来作为因子
            blendFunc.dst = GL_ZERO;        //不使用目标颜色
            img->setBlendFunc(blendFunc);
            
            CCRenderTexture* rt = CCRenderTexture::create(mask->getContentSize().width, mask->getContentSize().height);
            rt->begin();
            mask->visit();
            img->visit();
            rt->end();
            
            CCSprite* shadeImg = CCSprite::createWithTexture(rt->getSprite()->getTexture());
            shadeImg->setPosition(VisibleRect::center());
            //Y轴翻转
            shadeImg->setFlipY(true);
            layer->addChild(shadeImg);
//            layer->addChild(rt);
            
            
//            CCLayerColor* lc = CCLayerColor::create(ccc4(255, 255, 255, 255), 100, 100);
            
            shadeImg = DisplayObjectUtils::maskImg(img, CCSize(80, 50));
            shadeImg->setAnchorPoint(CCPointZero);
//            lc->cocos2d::CCNode::setPosition(100, 200);
//            lc->addChild(shadeImg);
            shadeImg->cocos2d::CCNode::setPosition(100, 200);
            layer->addChild(shadeImg);
            
        }
            break;
            
        case 2:{
            setTitle("遮罩2-ClippingNode 使用cocos2dx建立的默认工程，是不开启Stencil Buffer的，需要自己手动开启；\n开启办法：打开AppController.mm，将初始化EAGLView的代码里的GL_DEPTH_COMPONENT16改成GL_DEPTH24_STENCIL8_OES即可。  ");
            
            
            
            
        }
            
            break;
            
		default:
            break;
    }
            
	
	return layer;
}



