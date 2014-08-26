//
//  TestMultiAssetsManager.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-25.
//
//

#include "TestMultiAssetsManager.h"
#include "LuaEngineUtils.h"
#include "tolua++.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

NS_QING_BEGIN

bool TestMultiAssetsManager::init()
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

TestMultiAssetsManager::TestMultiAssetsManager()
: m_nPercent(0)
, m_bIsSuccessed(false)
, m_nErrorCode(0)
, m_pCallbackTarget(NULL)
, m_pCallbackFun(NULL)
, m_pManager(NULL)
, m_pTestLua1(NULL)
, m_pTestLua2(NULL)
{
    
}

TestMultiAssetsManager::~TestMultiAssetsManager()
{
//    CC_SAFE_RELEASE_NULL(m_pTestLua1);        //这里不能在release，否则崩溃
//    CC_SAFE_RELEASE_NULL(m_pTestLua2);
    CC_SAFE_DELETE(m_pManager);
}


void createDownloadedDir(string end)
{
    string str = CCFileUtils::sharedFileUtils()->getWritablePath();
    str += end;
    CCLOG("保存地址:%s", str.c_str());
    // Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *pDir = NULL;
    
    pDir = opendir (str.c_str());
    if (! pDir)
    {
        mkdir(str.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
#else
	if ((GetFileAttributesA(m_sPathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(str.c_str(), 0);
	}
#endif
}


void createLabel(CCNode *parent, string txt)
{
    CCLabelTTF *label = CCLabelTTF::create(txt.c_str(), FONT_NAME, FONT_SIZE);
    label->setPosition(VisibleRect::center());
    parent->addChild(label);
}

void TestMultiAssetsManager::onEnter()
{
	TestBaseLayer::onEnter();
    MultiAssetsManager *manager = new MultiAssetsManager("http://10.1.21.18/demo/");
    manager->removeDownload();
    m_pManager = manager;
    //===== 外部设置 ===========
    setCallback(this, callfunc_selector(TestMultiAssetsManager::onSuccessTest));
    
    manager->startDownload(this);
    
//    CC_SAFE_DELETE(manager);
    
}

void TestMultiAssetsManager::onExit()
{
	TestBaseLayer::onExit();

}


void TestMultiAssetsManager::setCallback(cocos2d::CCObject *callbackTarget, SEL_CallFunc callbackFun)
{
    this->m_pCallbackTarget = callbackTarget;
    this->m_pCallbackFun = callbackFun;
}

void TestMultiAssetsManager::onSuccessTest()
{
    CCLOG("下载成功了！做点什么。。。。");
    CCSprite* img = CCSprite::create("1_s.png");
    img->cocos2d::CCNode::setPosition(200, 300);
    addChild(img);
}



#pragma mark------------------------- 回调函数 -------------------------


void TestMultiAssetsManager::onProgress(int percent)
{
    m_nPercent = percent;
    CCLOG("下载进度 %d%%", percent);
}

void TestMultiAssetsManager::onSuccess()
{
    string str = "下载成功！";
    str += "\n";
    str += m_pManager->getStoragePath();
    str += m_pManager->getVersion();
    createLabel(this, str);
    CCLOG("MyAssetsManager::onSuccess ");
    m_bIsSuccessed = true;
    callBack();
    
    bool b = LuaEngineUtils::callLuaFunc("hello2.lua", "getNode", "");
    if(b){
        lua_State *ls = LuaEngineUtils::getLuaState();
        if(lua_istable(ls, -1)){
            lua_gettable(ls, -1);
            CCLOG("是个tabelE");
        }
        if(lua_isuserdata(ls, -1)){
            CCNode *luaNode = *(CCNode**) lua_touserdata(ls, -1);
            lua_pop(ls, 1);     //从堆栈中弹出,清除
            CC_SAFE_RETAIN(luaNode);        //不加会崩溃
            luaNode->setPosition(200, 200);
            CCSprite *luaSprite = NULL;//*(CCSprite**) lua_touserdata(ls, -1);
            CCLOG("lua getNode %p, %p, typeid: %s, %s", luaNode, luaSprite, typeid(luaNode).name(), typeid(luaSprite).name() );
            this->addChild(luaNode);
            CCLOG("转化成CCNode和CCSprite都对，都能显示");
            m_pTestLua1 = luaNode;
        }
    }else{
        CCLOG("调用 lua getNode 错误！");
    }
    
    b = LuaEngineUtils::callLuaFunc("hello2.lua", "getLuaNode", "");
    if(b){
        lua_State *ls = LuaEngineUtils::getLuaState();
        if(lua_isuserdata(ls, -1)){
            CCNode *luaNode = *(CCNode **) lua_touserdata(ls, -1);
            lua_pop(ls, 1);     //从堆栈中弹出,清除
            CC_SAFE_RETAIN(luaNode);
            luaNode->setPosition(200, 500);
            this->addChild(luaNode);
            CCLabelTTF *label = CCLabelTTF::create("lua Node add c++ label ttf", FONT_NAME, FONT_SIZE);
            luaNode->addChild(label);
            label->setPositionY(-30);
            m_pTestLua2 = luaNode;
        }
    }else{
        CCLOG("调用 lua getLuaNode 错误！");
    }
    
}

void TestMultiAssetsManager::onError(MultiAssetsManager::ErrorCode errorCode)
{
    string str = "下载失败！";
    str += "\n";
    str += m_pManager->getStoragePath();
    str += m_pManager->getVersion();
    char errStr[32];
    sprintf(errStr, "%d", errorCode);
    str += errStr;
    m_nErrorCode = errorCode;
    CCLOG("MyAssetsManager::onError %d", errorCode);
    switch (errorCode) {
        case MultiAssetsManager::kNoNewVersion:
            str += ("无新版本不需要更新,调用 onSuccess 函数");
            onSuccess();
            return;
            break;
            
        case MultiAssetsManager::kNetwork:
            str += ("网络 错误");
            break;
            
        case MultiAssetsManager::kCreateFile:
            str += ("文件IO 错误");
            break;
            
        case MultiAssetsManager::kUncompress:
            str += ("解压缩 错误！");
            break;
        default:
            break;
    }
    m_bIsSuccessed = false;
    callBack();
    createLabel(this, str);
}

void TestMultiAssetsManager::callBack()
{
    CCLOG("回调函数");
//    CC_SAFE_DELETE(m_pManager);           //manager 会销毁delegate，但delegate 指向自己
    if(m_pCallbackTarget && m_pCallbackFun){
        (m_pCallbackTarget->*m_pCallbackFun)();
    }
}

#pragma mark -









NS_QING_END