//
//  TestLuaDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-3-19.
//
//

#ifndef __QingLibCocos2dx__TestLuaDemo__
#define __QingLibCocos2dx__TestLuaDemo__

#include "Common.h"
#include "MyAssetsManagerDemo.h"

NS_QING_BEGIN


class TestLuaDemo : public MyAssetsManagerDemo
{
public:
    TestLuaDemo();
    CREATE_FUNC(TestLuaDemo);
	~TestLuaDemo();
    
protected:
    virtual void callBack();
    
    void runLua();
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestLuaDemo__) */
