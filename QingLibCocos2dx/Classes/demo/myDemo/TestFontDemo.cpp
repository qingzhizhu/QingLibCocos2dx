//
//  TestFontDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-1-16.
//
//

#include "TestFontDemo.h"

USING_NS_QING;


TestFontDemo::TestFontDemo()
{
    
}

TestFontDemo::~TestFontDemo()
{
}


CCLayer* TestFontDemo::getLayerByIndex()
{
    CCLayer * layer = CCLayer::create();
    string str = "font/Supercell-Magic.ttf";
    string titleAdd = "";
    switch (m_nLayerIndex) {
        case 0:
            str = "font/Supercell-Magic.ttf";
            break;
        case 1:
            str = "font/Abduction.ttf";
            break;
            
        case 2:
            titleAdd = "描边";
            break;
            
        case 3:
            titleAdd = "阴影";
            break;
            
        case 4:
            titleAdd = "描边+阴影";
            break;
            
        default:
            break;
    }
    showFont(str.c_str(), layer);
    if(m_nLayerIndex == 2){
        textAddOutline(titleAdd, layer);
    }else if(m_nLayerIndex == 3){
        textAddShadow(titleAdd, layer);  
    }else if(m_nLayerIndex == 4){
        textAddOutlineAndShadow(titleAdd, layer, 4);
    }
    
    return layer;
}


//static int fontCount = sizeof(fontList) / sizeof(*fontList);

static int vAlignIdx = 1;
static CCVerticalTextAlignment verticalAlignment[] =
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
};
static int vAlignCount = sizeof(verticalAlignment) / sizeof(*verticalAlignment);

void TestFontDemo::showFont(const char *pFont, CCLayer* target)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSize blockSize = CCSizeMake(s.width/3, 200);
    float fontSize = 36;
    
    target->removeChildByTag(kTagLabel1, true);
    target->removeChildByTag(kTagLabel2, true);
    target->removeChildByTag(kTagLabel3, true);
    target->removeChildByTag(kTagLabel4, true);
    target->removeChildByTag(kTagColor1, true);
    target->removeChildByTag(kTagColor2, true);
    target->removeChildByTag(kTagColor3, true);
    
    CCLabelTTF *top = CCLabelTTF::create(pFont, pFont, 24);
    CCLabelTTF *left = CCLabelTTF::create("alignment left 中文 か", pFont, fontSize,
                                          blockSize, kCCTextAlignmentLeft, verticalAlignment[vAlignIdx]);
    CCLabelTTF *center = CCLabelTTF::create("alignment center 中文", pFont, fontSize,
                                            blockSize, kCCTextAlignmentCenter, verticalAlignment[vAlignIdx]);
    CCLabelTTF *right = CCLabelTTF::create("alignment right 右部", pFont, fontSize,
                                           blockSize, kCCTextAlignmentRight, verticalAlignment[vAlignIdx]);
    
    CCLayerColor *leftColor = CCLayerColor::create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height);
    CCLayerColor *centerColor = CCLayerColor::create(ccc4(200, 100, 100, 255), blockSize.width, blockSize.height);
    CCLayerColor *rightColor = CCLayerColor::create(ccc4(100, 100, 200, 255), blockSize.width, blockSize.height);
    
    leftColor->ignoreAnchorPointForPosition(false);
    centerColor->ignoreAnchorPointForPosition(false);
    rightColor->ignoreAnchorPointForPosition(false);
    
    
    top->setAnchorPoint(ccp(0.5, 1));
    left->setAnchorPoint(ccp(0,0.5));
    leftColor->setAnchorPoint(ccp(0,0.5));
    center->setAnchorPoint(ccp(0,0.5));
    centerColor->setAnchorPoint(ccp(0,0.5));
    right->setAnchorPoint(ccp(0,0.5));
    rightColor->setAnchorPoint(ccp(0,0.5));
    
    top->setPosition(ccp(s.width/2,s.height-20));
    left->setPosition(ccp(0,s.height/2));
    leftColor->setPosition(left->getPosition());
    center->setPosition(ccp(blockSize.width, s.height/2));
    centerColor->setPosition(center->getPosition());
    right->setPosition(ccp(blockSize.width*2, s.height/2));
    rightColor->setPosition(right->getPosition());
    
    target->addChild(leftColor, -1, kTagColor1);
    target->addChild(left, 0, kTagLabel1);
    target->addChild(rightColor, -1, kTagColor2);
    target->addChild(right, 0, kTagLabel2);
    target->addChild(centerColor, -1, kTagColor3);
    target->addChild(center, 0, kTagLabel3);
    target->addChild(top, 0, kTagLabel4);
}



void TestFontDemo::textAddOutline(string titleAdd, CCLayer* target)
{
    CCLabelTTF* top = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel4));
    
    string temp1 = top->getString();
    titleAdd  =  temp1 + " | " + titleAdd;
    top->setString(titleAdd.c_str());
    
    //描边CCLabelTTF 左
    CCLabelTTF* left = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel1));
    temp1 = left->getString();
    const char* string = temp1.c_str();    
    const char* fontName = left->getFontName();
    int fontSize = left->getFontSize();
    ccColor3B color3 = left->getColor();
    CCVerticalTextAlignment vertical =  left->getVerticalAlignment();
    CCTextAlignment horizontal = left->getHorizontalAlignment();
    CCSize dimensions = left->getDimensions();
    int lineWidth = 2;
    
    left->setColor(ccBLACK);
    
    //描边CCLabelTTF 右
    CCLabelTTF* right = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    right->setColor(ccBLACK);
    right->setPosition(ccp(left->getContentSize().width*0.5+lineWidth*2,left->getContentSize().height*0.5));
    left->addChild(right);
    
    //描边CCLabelTTF 上
    CCLabelTTF* up = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    up->setColor(ccBLACK);
    up->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5+lineWidth));
    left->addChild(up);
    
    //描边CCLabelTTF 下
    CCLabelTTF* down = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    down->setColor(ccBLACK);
    down->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5-lineWidth));
    left->addChild(down);
    
    //正文CCLabelTTF
    CCLabelTTF* center = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    center->setColor(color3);
    center->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5));
    left->addChild(center);
    
    
    
}


void TestFontDemo::textAddShadow(string titleAdd, cocos2d::CCLayer *target, int shadowSize, int shadowOpacity)
{
    CCLabelTTF* top = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel4));
    string temp1 = top->getString();
    titleAdd  +=  temp1 + " | " + titleAdd;
    top->setString(titleAdd.c_str());
    
    //描边CCLabelTTF 左
    CCLabelTTF* shadow = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel2));
    temp1 = shadow->getString();
    const char* string = temp1.c_str();
    const char* fontName = shadow->getFontName();
    int fontSize = shadow->getFontSize();
    ccColor3B color3 = shadow->getColor();
    CCVerticalTextAlignment vertical =  shadow->getVerticalAlignment();
    CCTextAlignment horizontal = shadow->getHorizontalAlignment();
    CCSize dimensions = shadow->getDimensions();
//    int lineWidth = 2;
        
    shadow->setColor(ccBLACK);
    
    CCLabelTTF* center = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    center->setColor(color3);
    center->setPosition(ccp(shadow->getContentSize().width*0.5-shadowSize, shadow->getContentSize().height*0.5+shadowSize));
    shadow->addChild(center);
    
}


void TestFontDemo::textAddOutlineAndShadow(string titleAdd, cocos2d::CCLayer *target, int shadowSize, int shadowOpacity)
{
    CCLabelTTF* top = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel4));
    
    string temp1 = top->getString();
    titleAdd  =  temp1 + " | " + titleAdd;
    top->setString(titleAdd.c_str());
    
    CCLabelTTF* shadow = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel3));
    temp1 = shadow->getString();
    const char* string = temp1.c_str();
    const char* fontName = shadow->getFontName();
    int fontSize = shadow->getFontSize();
    ccColor3B color3 = shadow->getColor();
    CCVerticalTextAlignment vertical =  shadow->getVerticalAlignment();
    CCTextAlignment horizontal = shadow->getHorizontalAlignment();
    CCSize dimensions = shadow->getDimensions();
    int lineWidth = 2;
    
    
    shadow->setColor(ccBLACK);
    shadow->setOpacity(shadowOpacity);
    
    
    
    CCLabelTTF* left = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    left->setColor(ccBLACK);
    left->setPosition(ccp(shadow->getContentSize().width*0.5-shadowSize, shadow->getContentSize().height*0.5+shadowSize));
    shadow->addChild(left);
    
    CCLabelTTF* right = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    right->setColor(ccBLACK);
    right->setPosition(ccp(left->getContentSize().width*0.5+lineWidth*2,left->getContentSize().height*0.5));
    left->addChild(right);
    
    CCLabelTTF* up = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    up->setColor(ccBLACK);
    up->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5+lineWidth));
    left->addChild(up);
    
    CCLabelTTF* down = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    down->setColor(ccBLACK);
    down->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5-lineWidth));
    left->addChild(down);
    
    CCLabelTTF* center = CCLabelTTF::create(string, fontName, fontSize, dimensions, horizontal, vertical);
    center->setColor(color3);
    center->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5));
    left->addChild(center);
}






