//
//  MyAssetsManager.cpp
//  QingLibCocos2dxLua
//
//  Created by Kevin Geng on 14-3-12.
//
//

#include "MyAssetsManager.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

USING_NS_QING;


MyAssetsManager::MyAssetsManager()
: m_nPercent(0)
, m_sPathToSave("")
, m_sPackageUrl("")
, m_sVersionUrl("")
, m_bIsSuccessed(false)
, m_nErrorCode(0)
, m_pCallbackTarget(NULL)
, m_pCallbackFun(NULL)
, m_bIsUpdated(false)
{
    init();
}

MyAssetsManager::MyAssetsManager(string packageUrl, string versionUrl, CCObject* callbackTarget, SEL_CallFunc callbackFun)
: m_nPercent(0)
, m_sPathToSave("")
, m_sPackageUrl(packageUrl)
, m_sVersionUrl(versionUrl)
, m_bIsSuccessed(false)
, m_nErrorCode(0)
, m_pCallbackTarget(callbackTarget)
, m_pCallbackFun(callbackFun)
, m_bIsUpdated(false)
{
    init();
}

MyAssetsManager::~MyAssetsManager()
{
    
}

void MyAssetsManager::init()
{
    createDownloadedDir();
    
}


void MyAssetsManager::setSearchPaths()
{
    // Should set search resource path before running script if "update" is not clicked.
    // Because AssetsManager will set
    if (!m_bIsUpdated)
    {
        vector<string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), m_sPathToSave);
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }
}



#pragma mark -回调函数

void MyAssetsManager::onProgress(int percent)
{
    m_nPercent = percent;
    CCLOG("下载进度 %d%%", percent);
}

void MyAssetsManager::onSuccess()
{
    CCLOG("MyAssetsManager::onSuccess ");
    m_bIsSuccessed = true;
    callBack();
}

void MyAssetsManager::onError(AssetsManager::ErrorCode errorCode)
{
    m_nErrorCode = errorCode;
    CCLOG("MyAssetsManager::onError %d", errorCode);
    switch (errorCode) {
        case cocos2d::extension::AssetsManager::kNoNewVersion:
            CCLOG("无新版本不需要更新,调用 onSuccess 函数");
            onSuccess();
            return;
            break;
            
        case cocos2d::extension::AssetsManager::kNetwork:
            CCLOG("网络 错误");
            break;
            
        case cocos2d::extension::AssetsManager::kCreateFile:
            CCLOG("文件IO 错误");
            break;
            
        case cocos2d::extension::AssetsManager::kUncompress:
            CCLOG("解压缩 错误！");
            break;
        default:
            break;
    }
    m_bIsSuccessed = false;
    callBack();
}

void MyAssetsManager::callBack()
{
    CCLOG("回调函数");
    if(m_pCallbackTarget && m_pCallbackFun){
        (m_pCallbackTarget->*m_pCallbackFun)();
    }
}

#pragma mark -


static AssetsManager *pAssetsManager = NULL;

AssetsManager* MyAssetsManager::getAssetsManager()
{
    if(m_sVersionUrl.size() == 0 ||
     m_sPackageUrl.size() == 0 ||
     std::string::npos == m_sPackageUrl.find(".zip")){
        CCLOG("没设置资源包url和版本");
        m_sPackageUrl = "http://10.1.21.107/demo/package.zip";
        m_sVersionUrl = "http://10.1.21.107/demo/version";
    }
    
    if (! pAssetsManager)// || pAssetsManager->getPackageUrl() != m_sPackageUrl )
    {
        pAssetsManager = new AssetsManager(m_sPackageUrl.c_str(), m_sVersionUrl.c_str(), m_sPathToSave.c_str());
        
        pAssetsManager->setDelegate(this);
        pAssetsManager->setConnectionTimeout(3);
    }
    return pAssetsManager;
}

void MyAssetsManager::createDownloadedDir()
{
    m_sPathToSave = CCFileUtils::sharedFileUtils()->getWritablePath();
    m_sPathToSave += "tmpdir_k";
    CCLOG("保存地址:%s", m_sPathToSave.c_str());
    // Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *pDir = NULL;
    
    pDir = opendir (m_sPathToSave.c_str());
    if (! pDir)
    {
        mkdir(m_sPathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
#else
	if ((GetFileAttributesA(m_sPathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(m_sPathToSave.c_str(), 0);
	}
#endif
}


void MyAssetsManager::startDownload()
{
    m_bIsSuccessed = false;
    // update resources
    getAssetsManager()->update();
    
    m_bIsUpdated = true;
}

void MyAssetsManager::removeDownload()
{
    
    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    string command = "rm -r ";
    // Path may include space.
    command += "\"" + m_sPathToSave + "\"";
    system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + m_sPathToSave + "\"";
    system(command.c_str());
#endif
    // Delete recorded version codes.
    getAssetsManager()->deleteVersion();
    
    createDownloadedDir();
}

