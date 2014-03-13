//
//  LabelUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-2-11.
//
//

#include "LabelUtils.h"

USING_NS_QING;


LabelUtils::LabelUtils()
{
	
}

LabelUtils::~LabelUtils()
{
	
}


//label 描边
void LabelUtils::createStroke(CCLabelTTF *label, float size, ccColor3B color)
{
    CCSize originalSize = label->getTexture()->getContentSize();
    float wid = originalSize.width + size * 2;
    float hei = originalSize.height + size * 2;
    CCPoint originalPos = label->getPosition();
    CCPoint originalAnchor = label->getAnchorPoint();
    ccColor3B originalColor = label->getColor();
    ccBlendFunc originalBlend = label->getBlendFunc();
    CCNode* node = label->getChildByTag(TAG_STROKE);
    CCRenderTexture* rt = NULL;
    if(node){
        rt = dynamic_cast<CCRenderTexture*>(node);
        if(rt){
//            rt->clear(0, 0, 0, 0);        //这里有问题，会有一个黑色块
//            CCLOG("use pre-existing CCrenderTexture!");
            rt->removeFromParentAndCleanup(true);
            rt = NULL;
        }
    }
    if(!rt){
        rt = CCRenderTexture::create(wid, hei);
    }
    label->setColor(color);
    label->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA, GL_ONE});
    
    //    rt->setAnchorPoint(originalAnchor); //没用
    CCPoint center = ccp(wid * originalAnchor.x, hei * originalAnchor.y);
    rt->beginWithClear(0, 0, 0, 0);
    for(int i=0; i<360; i+= 15){
        float radians = CC_DEGREES_TO_RADIANS(i);
        label->cocos2d::CCNode::setPosition(center.x + sin(radians)*size, center.y + cos(radians)*size);
        label->visit();
    }
    rt->end();
    
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    
    float rtX = originalSize.width / 2 + size;
    float rtY = originalSize.height / 2 - size;
    rt->setPosition(rtX, rtY);
    
    if(rt->getParent() == NULL) label->addChild(rt, -100, TAG_STROKE);
    
    //测试
    //    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 128), wid, hei);
    //    layer->setPosition(rt->getPosition());
    //    label->addChild(layer);
}