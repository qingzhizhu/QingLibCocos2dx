//
//  AssetsManagerDemo.cpp
//  QingLibCocos2dxLua
//
//  Created by Kevin Geng on 14-3-13.
//
//

#include "AssetsManagerDemo.h"
#include "MyAssetsManager.h"

#include "CCLuaEngine.h"

#include "QingSprite.h"

USING_NS_QING;


CCScene* AssetsManagerDemo::scene()
{
    CCScene * scene = CCScene::create();
    scene->addChild(new AssetsManagerDemo());
    return scene;
}

static MyAssetsManager * manager = NULL;

AssetsManagerDemo::AssetsManagerDemo()
{
    manager = new MyAssetsManager("http://10.1.21.16:8099/demo/package.zip", "http://10.1.21.16:8099/demo/version", this, callfunc_selector(AssetsManagerDemo::callBack));
    manager->removeDownload();        //若主动删除文件内容，version信息不会更新
    manager->startDownload();
}

AssetsManagerDemo::~AssetsManagerDemo()
{
    
}

void AssetsManagerDemo::callBack()
{
    CCLOG("更新完毕！");
    if(!manager->getIsSuccessed()) return;
    CCSprite* img = CCSprite::create("I_9.png");
    img->cocos2d::CCNode::setPosition(200, 300);
    addChild(img);
    img = CCSprite::create("I_06.png");
    img->cocos2d::CCNode::setPosition(100, 100);
    addChild(img);
    
    img = CCSprite::create("I_15.png");
    img->cocos2d::CCNode::setPosition(200, 200);
    addChild(img);
    
    
//    QingSprite* img2 = QingSprite::createQingSprite("Icon.png");
//    img2->cocos2d::CCNode::setPosition(200, 300);
//    addChild(img2);
    
    runLua();
}


void AssetsManagerDemo::runLua()
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
