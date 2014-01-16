//
//  TestBaseDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-1-16.
//
//
/// 底部带回退，重置，前进按钮

#ifndef __QingLibCocos2dx__TestBaseDemo__
#define __QingLibCocos2dx__TestBaseDemo__

#include "Common.h"
#include "TestBaseLayer.h"

NS_QING_BEGIN


class TestBaseDemo : public TestBaseLayer
{
public:
    TestBaseDemo();
    CREATE_FUNC(TestBaseDemo);
	~TestBaseDemo();
    
protected:
    
    virtual void onEnter();
    
    //--------------- bottom ui -------------
    void addBottomUI();
    void backCallback();
    void restartCallback();
    void nextCallback();
    
    void addDemoLayer();
    
    /**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex() { return NULL; }
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 2; }
    
    //--------------- bottom ui end -------------
    
    
    
protected:
    CCNode* m_pContainer;
    int m_nLayerIndex;
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestBaseDemo__) */
