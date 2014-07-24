//
//  TestLocalLuaDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-23.
//
//

#include "TestLocalLuaDemo.h"
#include "LuaEngineUtils.h"

USING_NS_QING;

bool TestLocalLuaDemo::init()
{
	bool bRet = false;
	do
	{
	    m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestLocalLuaDemo::TestLocalLuaDemo()
{
    
}

TestLocalLuaDemo::~TestLocalLuaDemo()
{
    
}

CCLayer* TestLocalLuaDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
	switch (m_nLayerIndex) {
        case 0:{
            lua_State* ls = LuaEngineUtils::getLuaStateByFunName("lua/hello2.lua", "myadd");
            if(!ls){
                CCLOG("错误！！！");
                return layer;
            }
            lua_pushinteger(ls, 54);
            lua_pushinteger(ls, 23);
            
            /*
             lua_call
             第一个参数:函数的参数个数
             第二个参数:函数返回值个数
             */
            lua_call(ls, 2, 1);
            
            int result = lua_tonumber(ls, -1);
            CCLOG("result = %d", result);
            
        }
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

