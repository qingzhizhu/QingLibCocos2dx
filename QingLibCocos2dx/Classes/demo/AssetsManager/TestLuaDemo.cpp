//
//  TestLuaDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-3-19.
//
//

#include "TestLuaDemo.h"
#include "CCLuaEngine.h"


extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

USING_NS_QING;


TestLuaDemo::TestLuaDemo()
{
	// TODO: auto generated code
}

TestLuaDemo::~TestLuaDemo()
{
	// TODO: auto generated code
}

void TestLuaDemo::callBack()
{
    MyAssetsManagerDemo::callBack();
    
    runLua();
}





const char* getFileFullPath(const char* fileName){
    return CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName).c_str();
}



void TestLuaDemo::runLua()
{
    //    if(CCDirector::sharedDirector()->getRunningScene() == NULL){
    //        CCLOG("runing scene is NULl");
    //        runLua();
    //        return;
    //    }
    CCLOG("scene %d", CCDirector::sharedDirector()->getRunningScene() != NULL);
    // register lua engine
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("hello.lua");
    pEngine->executeScriptFile(path.c_str());
    
    
    
    
//    
//    lua_State* pl = lua_open();
//    luaopen_base(pl);
//    
//    // 执行脚本
//    luaL_dofile(pl, "hello2.lua");
//    
//    //放在堆栈中
//    lua_getglobal(pl, "myadd");
//    
//    //传参
//    lua_pushinteger(pl, 133);
//    lua_pushinteger(pl, 3433);
//
//    //执行函数, 2是参数个数，1是返回个数
//    lua_call(pl, 2, 1);
//    
//    
//    int result = lua_tonumber(pl, -1);
//    CCLOG("result = %d", result);
    
    
    //------------
    const char* luaFileName = "hello2.lua";
    const char* functionName = "myadd";
    lua_State*  ls = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    
    int isOpen = luaL_dofile(ls, getFileFullPath(luaFileName));
    if(isOpen!=0){
        CCLOG("Open Lua Error: %i", isOpen);
//        return NULL;
    }
    
    lua_getglobal(ls, functionName);
    
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
