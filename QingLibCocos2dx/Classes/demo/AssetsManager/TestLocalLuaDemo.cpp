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
            setTitle("C++ 调用 Lua 方法");
//            lua_State* ls = LuaEngineUtils::getLuaStateByFunName("lua/hello2.lua", "myadd");
//            if(!ls){
//                CCLOG("错误！！！");
//                return layer;
//            }
//            lua_pushinteger(ls, 54);
//            lua_pushinteger(ls, 23);
//            
//            /*
//             lua_call
//             第一个参数:函数的参数个数
//             第二个参数:函数返回值个数
//             */
//            lua_call(ls, 2, 1);
//            
//            int result = lua_tonumber(ls, -1);
//            CCLOG("result = %d", result);
            /*
            const char * temp = "abcd";
            CCLOG("temp0 值=%s", temp);
            ++temp;
            CCLOG("temp1 值=%s", temp);
            ++temp;
            CCLOG("temp2 值=%s", temp);
            temp-= 1;
            temp-= 3;
            CCLOG("temp0 值=%s", temp);
             */
            
            //抽象后调用
            string str = "";
            int result = LuaEngineUtils::callLuaFuncReturnInt("lua/hello2.lua", "myadd", "%d%d", 54, 23);
            CCLOG("result = %d", result);
            str += "调用lua function myadd(x, y) ";
            str += result == 77 ? " ok!" : "Error";
            str += "\n";
            
            result = LuaEngineUtils::callLuaFuncReturnInt("lua/hello2.lua", "funReturnInt", "%d%s%b", 100, "aaa", true);
            str += "调用lua funReturnInt(nNum, str, bIsOk) ";
            str += result == 1000 ? " ok!" : "Error";
            str += "\n";
            
            string resultStr = LuaEngineUtils::callLuaFuncReturnChar("lua/hello2.lua", "funReturnString", "%d%s%b", 999, ";Kevin;", true);
            str += "调用lua callLuaFuncReturnChar(nNum, str, bIsOk) ";
            str += resultStr == "999;Kevin;true" ? " ok!" : "Error";
            str += "\n";
            
            bool resultB = LuaEngineUtils::callLuaFuncReturnBool("lua/hello2.lua", "funReturnBool", "%d%s%b", 100, "aaa", true);
            str += "调用lua callLuaFuncReturnBool(nNum, str, bIsOk) ";
            str += resultB ? " ok!" : "Error";
            str += "\n";
            
            createLabel(layer, str);
            
        }
            break;
            
        case 1:{
            setTitle("Lua 调用 C++ 函数！");
            
            
        }
            break;
		default:
            break;
    }
            
	
	return layer;
}

