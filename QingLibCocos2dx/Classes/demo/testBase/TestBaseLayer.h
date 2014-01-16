//
//  TestBaseLayer.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//
/// 测试的基类layer

#ifndef __QingLibCocos2dx__TestBaseLayer__
#define __QingLibCocos2dx__TestBaseLayer__

#include "Common.h"

NS_QING_BEGIN


class TestBaseLayer : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(TestBaseLayer);
	TestBaseLayer();
	virtual ~TestBaseLayer();
    
    virtual void onEnter() ;
    
    virtual void runThisLayer();
    
    
protected:
    virtual void nextAction() { }
    
    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);

};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestBaseLayer__) */
