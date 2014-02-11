//
//  TestFontDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-1-16.
//
//

#include "TestFontDemo.h"
#include "LabelUtils.h"

USING_NS_QING;


TestFontDemo::TestFontDemo()
{
    CCLayer* layer = CCLayerColor::create(ccc4(0xFF, 0x99, 0xCC, 0xEE));
    addChild(layer, -100);
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
            
        case 5:
            titleAdd = "新阴影描边";
            break;
            
        default:
            break;
    }
    showFont(str.c_str(), layer);
    CCLabelTTF* lbl1 = dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagLabel1));
    CCLabelTTF* lbl2 = dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagLabel2));
    CCLabelTTF* lbl3 = dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagLabel3));
    if(m_nLayerIndex == 2){
        textAddOutline(lbl1, titleAdd, layer);
        textAddOutline(lbl2, titleAdd, layer);
        textAddOutline(lbl3, titleAdd, layer);
    }else if(m_nLayerIndex == 3){
        textAddShadow(lbl1, titleAdd, layer);
        textAddShadow(lbl2, titleAdd, layer);
        textAddShadow(lbl3, titleAdd, layer);
    }else if(m_nLayerIndex == 4){
        textAddOutlineAndShadow(lbl1, titleAdd, layer, 4);
        textAddOutlineAndShadow(lbl2, titleAdd, layer, 4);
        textAddOutlineAndShadow(lbl3, titleAdd, layer, 4);
        
    }else if(m_nLayerIndex == 5){
        lbl2->getParent()->addChild(createStroke(dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagLabel4)), 2, ccBLACK), -1);
        lbl2->getParent()->addChild(createStroke(lbl2, 2, ccBLACK), -1);
        lbl2->getParent()->addChild(createStroke(lbl1, 2, ccBLACK), -1);
        lbl2->getParent()->addChild(createStroke(lbl3, 2, ccBLACK), -1);
    }else if(m_nLayerIndex == 6){
//        createStroke2(dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagLabel4)), 2, ccBLACK);
//        createStroke2(lbl2, 2, ccBLACK);
//        createStroke2(lbl1, 2, ccBLACK);
//        createStroke2(lbl3, 2, ccBLACK);
//        createStroke2(dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagTest1)), 2, ccBLACK);
        LabelUtils::createStroke(dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagLabel4)), 2, ccBLACK);
        LabelUtils::createStroke(lbl2, 1, ccBLACK);
        LabelUtils::createStroke(lbl1);
        LabelUtils::createStroke(lbl3);
        LabelUtils::createStroke(dynamic_cast<CCLabelTTF*>(layer->getChildByTag(kTagTest1)), 1, ccGREEN);
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
//static int vAlignCount = sizeof(verticalAlignment) / sizeof(*verticalAlignment);

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
    
    top->setPosition(ccp(s.width/2,s.height-40));
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
    
    
    CCLabelTTF* lbl = CCLabelTTF::create("this is test label!", FONT_NAME, fontSize);
    lbl->setPosition(ccp(s.width/2,s.height-120));
    target->addChild(lbl, 0, kTagTest1);
}



void TestFontDemo::textAddOutline(CCLabelTTF* targetLbl, string titleAdd, CCLayer* target)
{
    CCLabelTTF* top = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel4));
    
    string temp1 = top->getString();
    titleAdd  =  temp1 + " | " + titleAdd;
    top->setString(titleAdd.c_str());
    
    //描边CCLabelTTF 左
    CCLabelTTF* left = targetLbl;//dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel1));
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


void TestFontDemo::textAddShadow(CCLabelTTF* targetLbl, string titleAdd, cocos2d::CCLayer *target, int shadowSize, int shadowOpacity)
{
    CCLabelTTF* top = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel4));
    string temp1 = top->getString();
    titleAdd  +=  temp1 + " | " + titleAdd;
    top->setString(titleAdd.c_str());
    
    //描边CCLabelTTF 左
    CCLabelTTF* shadow = targetLbl;//dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel2));
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


void TestFontDemo::textAddOutlineAndShadow(CCLabelTTF* targetLbl, string titleAdd, cocos2d::CCLayer *target, int shadowSize, int shadowOpacity)
{
    CCLabelTTF* top = dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel4));
    
    string temp1 = top->getString();
    titleAdd  =  temp1 + " | " + titleAdd;
    top->setString(titleAdd.c_str());
    
    CCLabelTTF* shadow = targetLbl;//dynamic_cast<CCLabelTTF*>(target->getChildByTag(kTagLabel3));
    temp1 = shadow->getString();
    const char* string = temp1.c_str();
    const char* fontName = shadow->getFontName();
    int fontSize = shadow->getFontSize();
    ccColor3B color3 = shadow->getColor();
    CCVerticalTextAlignment vertical =  shadow->getVerticalAlignment();
    CCTextAlignment horizontal = shadow->getHorizontalAlignment();
    CCSize dimensions = shadow->getDimensions();
    int lineWidth = 1;
    
    
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



//label 描边
CCRenderTexture* TestFontDemo::createStroke(CCLabelTTF *label, float size, ccColor3B color)
{
    float x=label->getTexture()->getContentSize().width+size*2;
    float y=label->getTexture()->getContentSize().height+size*2;
    CCRenderTexture *rt=CCRenderTexture::create(x, y);
    CCPoint originalPos=label->getPosition();
    ccColor3B originalColor=label->getColor();
    label->setColor(color);
    ccBlendFunc originalBlend=label->getBlendFunc();
    label->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA,GL_ONE});
    CCPoint anchorPoint = label->getAnchorPoint();
    CCPoint center=ccp(x*anchorPoint.x +size, y*anchorPoint.y + size);
    
    rt->begin();
    for (int i=0; i<360; i+=15) {
        float _x=center.x+sin(CC_DEGREES_TO_RADIANS(i))*size;
        float _y=center.y+cos(CC_DEGREES_TO_RADIANS(i))*size;
        
        label->setPosition(ccp(_x, _y));
        label->visit();
        
    }
    rt->end();
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    float rtX=originalPos.x-size  + (0.5 - anchorPoint.x) * label->getTexture()->getContentSize().width;
    float rtY=originalPos.y-size + (0.5 - anchorPoint.y) * label->getTexture()->getContentSize().height;
    rt->setAnchorPoint(label->getAnchorPoint());
    rt->setPosition(ccp(rtX, rtY));
    
    return rt;
    
}

//label 描边
void TestFontDemo::createStroke2(CCLabelTTF *label, float size, ccColor3B color)
{
    CCSize originalSize = label->getTexture()->getContentSize();
    float wid = originalSize.width + size * 2;
    float hei = originalSize.height + size * 2;
    CCPoint originalPos = label->getPosition();
    CCPoint originalAnchor = label->getAnchorPoint();
    ccColor3B originalColor = label->getColor();
    ccBlendFunc originalBlend = label->getBlendFunc();
    CCRenderTexture* rt = CCRenderTexture::create(wid, hei);
    
    label->setColor(color);
    label->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA, GL_ONE});
    
//    rt->setAnchorPoint(originalAnchor); //没用
    CCPoint center = ccp(wid * originalAnchor.x, hei * originalAnchor.y);
    rt->beginWithClear(0, 0, 0, 0);
//    rt->begin();
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
    
    label->addChild(rt, -1);
    
//    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 128), wid, hei);
//    layer->setPosition(rt->getPosition());
//    label->addChild(layer);
}



