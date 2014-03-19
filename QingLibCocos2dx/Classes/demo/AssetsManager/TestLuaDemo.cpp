//
//  TestLuaDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-3-19.
//
//

#include "TestLuaDemo.h"
#include "CCLuaEngine.h"

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
    
    
}