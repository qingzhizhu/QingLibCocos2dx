//
//  TestMultiAssetsManager.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-25.
//
//

#include "TestMultiAssetsManager.h"

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
{
    
}

TestMultiAssetsManager::~TestMultiAssetsManager()
{
    
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

void TestMultiAssetsManager::onEnter()
{
	TestBaseLayer::onEnter();
    MultiAssetsManager *manager = new MultiAssetsManager("http://localhost/demo/");
//    manager->removeDownload();
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
}



#pragma mark------------------------- 回调函数 -------------------------


void TestMultiAssetsManager::onProgress(int percent)
{
    m_nPercent = percent;
    CCLOG("下载进度 %d%%", percent);
}

void TestMultiAssetsManager::onSuccess()
{
    CCLOG("MyAssetsManager::onSuccess ");
    m_bIsSuccessed = true;
    callBack();
}

void TestMultiAssetsManager::onError(MultiAssetsManager::ErrorCode errorCode)
{
    m_nErrorCode = errorCode;
    CCLOG("MyAssetsManager::onError %d", errorCode);
    switch (errorCode) {
        case MultiAssetsManager::kNoNewVersion:
            CCLOG("无新版本不需要更新,调用 onSuccess 函数");
            onSuccess();
            return;
            break;
            
        case MultiAssetsManager::kNetwork:
            CCLOG("网络 错误");
            break;
            
        case MultiAssetsManager::kCreateFile:
            CCLOG("文件IO 错误");
            break;
            
        case MultiAssetsManager::kUncompress:
            CCLOG("解压缩 错误！");
            break;
        default:
            break;
    }
    m_bIsSuccessed = false;
    callBack();
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