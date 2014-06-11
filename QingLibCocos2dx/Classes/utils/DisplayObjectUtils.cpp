//
//  DisplayObjectUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-4-8.
//
//

#include "DisplayObjectUtils.h"

USING_NS_QING;


DisplayObjectUtils::DisplayObjectUtils()
{
	// TODO: auto generated code
}

DisplayObjectUtils::~DisplayObjectUtils()
{
	// TODO: auto generated code
}


#pragma mark- 图片相关

void DisplayObjectUtils::repeatImg(CCSprite *img, const CCSize &size)
{
    if(!img) return;
    img->setTextureRect(CCRectMake(0, 0, size.width, size.height));
    ccTexParams  params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    img->getTexture()->setTexParameters(&params);
    
}

CCSprite* DisplayObjectUtils::maskImg(CCSprite *src, const CCSize &size)
{
    
    return maskImg(src, CCLayerColor::create(ccc4(0xFF, 0xFF, 0xFF, 0xFF), size.width, size.height));
}

CCSprite* DisplayObjectUtils::maskImg(CCSprite *src, CCBlendProtocol *mask)
{
    if(src == NULL || mask == NULL) return NULL;
    CCNode* maskDis = dynamic_cast<CCNode*>(mask);
    if(!maskDis){
        CCLOG("mask 不是 显示对象..");
        return NULL;
    }
    //src 表示使用目标颜色的alpha值来作为因子, dst 不使用目标颜色
    src->setBlendFunc((ccBlendFunc){GL_DST_ALPHA, GL_ZERO});
    mask->setBlendFunc((ccBlendFunc){GL_ONE, GL_ZERO});
    CCRenderTexture* rt = CCRenderTexture::create(maskDis->getContentSize().width, maskDis->getContentSize().height);
    rt->begin();
    maskDis->visit();
    src->visit();
    rt->end();
    CCSprite* result = CCSprite::createWithTexture(rt->getSprite()->getTexture());
    //Y轴翻转
    result->setFlipY(true);
    return result;
}

#pragma mark- 其他

CCNode* DisplayObjectUtils::getChildByTagRecursive(CCNode *containerLayer, int tagIdOfChild)
{
    if(containerLayer && containerLayer->getChildren()){
        if(containerLayer->getChildren()->count() > 0){
            CCObject* child = NULL;
            CCARRAY_FOREACH(containerLayer->getChildren(), child){
                CCNode* pChild = (CCNode*) child;
                if(pChild->getTag() == tagIdOfChild){
                    CCLOG("get 1 ========================,%d",tagIdOfChild);
                    return pChild;
                }else{
                    CCNode* result = getChildByTagRecursive(pChild, tagIdOfChild);
                    if(result){
                        return result;
                    }
                }
            }
        }else if(containerLayer->getTag() == tagIdOfChild){
            CCLOG("get 2 ========================,%d",tagIdOfChild);
            return containerLayer;
        }
    }
    
    return NULL;
}




