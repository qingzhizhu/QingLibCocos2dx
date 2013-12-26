//
//  TestMyDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#ifndef __QingLibCocos2dx__TestMyDemo__
#define __QingLibCocos2dx__TestMyDemo__

#include "Common.h"
#include "TestBaseLayer.h"

NS_QING_BEGIN


class TestMyDemo : public TestBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(TestMyDemo);
	TestMyDemo();
	virtual ~TestMyDemo();
    
    virtual void onEnter();
    
    virtual void onExit() { TestBaseLayer::onExit(); addScheduler(false); }
    
protected:
    void addScheduler(bool isAdd);
    
    void doEnterFrame(float time);

    CCLabelTTF* m_pLbl;
    
    /**超过这个高度进行滚动*/
    int m_nHei; //= 90;
    
    /**文本的实际高度*/
    int m_nLblHei;
    int m_nLblWid;
    
    /**文本移动像素*/
    int m_nMoved;
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestMyDemo__) */
