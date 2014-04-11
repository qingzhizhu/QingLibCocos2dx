//
//  TestClippingNodeDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-4-11.
//
//
/// 底部带回退，重置，前进按钮

#ifndef __QingLibCocos2dx__TestClippingNodeDemo__
#define __QingLibCocos2dx__TestClippingNodeDemo__

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN


class TestClippingNodeDemo : public TestBaseDemo
{
public:
	virtual bool init();
	CREATE_FUNC(TestClippingNodeDemo);
	TestClippingNodeDemo();
	virtual ~TestClippingNodeDemo();

	/**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 2; }
    
    virtual void update(float delta);
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher();
protected:
    CCNode* m_pRect;
    
    CCNode* m_pClip;
    CCNode* m_pImgTip;
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestClippingNodeDemo__) */
