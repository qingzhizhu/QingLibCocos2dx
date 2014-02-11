//
//  TestFontDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-1-16.
//
//

#ifndef __QingLibCocos2dx__TestFontDemo__
#define __QingLibCocos2dx__TestFontDemo__

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN

enum {
    kTagLabel1,
    kTagLabel2,
    kTagLabel3,
    kTagLabel4,
    
    kTagColor1,
    kTagColor2,
    kTagColor3,
    
    kTagTest1,
};

class TestFontDemo : public TestBaseDemo
{
public:
    TestFontDemo();
    CREATE_FUNC(TestFontDemo);
	~TestFontDemo();
    
    /**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 7; }
    
    
protected:
    void showFont(const char *pFont, CCLayer* target);
    
    /**描边1*/
    void textAddOutline(CCLabelTTF* targetLbl, string titleAdd, CCLayer* target);
    /**阴影1*/
    void textAddShadow(CCLabelTTF* targetLbl, string titleAdd, CCLayer* target, int shadowSize=2, int shadowOpacity=200);
    /**描边阴影1*/
    void textAddOutlineAndShadow(CCLabelTTF* targetLbl, string titleAdd, CCLayer* target, int shadowSize=2, int shadowOpacity=200);
    
    
    
    CCRenderTexture* createStroke(CCLabelTTF *label, float size, ccColor3B color);
    
    /**这个是加在lbl里面*/
    void createStroke2(CCLabelTTF *label, float size, ccColor3B color);
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestFontDemo__) */
