//
//  TestController.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#ifndef __QingLibCocos2dx__TestController__
#define __QingLibCocos2dx__TestController__

#include "Common.h"

NS_QING_BEGIN


class TestController : public CCLayer
{
public:
    TestController();
    CREATE_FUNC(TestController);
	~TestController();
    
    /**如果*/
    virtual bool init();
    
    void menuCallback(CCObject * pSender);
    /**关闭按钮事件*/
    void closeCallback(CCObject * pSender);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    
private:
    CCPoint m_tBeginPos;
    CCMenu* m_pItemMenu;
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestController__) */
