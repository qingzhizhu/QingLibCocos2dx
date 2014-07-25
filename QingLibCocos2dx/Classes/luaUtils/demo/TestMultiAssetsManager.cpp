//
//  TestMultiAssetsManager.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-25.
//
//

#include "TestMultiAssetsManager.h"
#include "MultiAssetsManager.h"

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
		// TODO: auto generated code
        m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestMultiAssetsManager::TestMultiAssetsManager()
{
	// TODO: auto generated code
}

TestMultiAssetsManager::~TestMultiAssetsManager()
{
	// TODO: auto generated code
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
    string storeStr = CCFileUtils::sharedFileUtils()->getWritablePath() + "aaaa";
    createDownloadedDir("aaaa");
    MultiAssetsManager *manager = new MultiAssetsManager("http://localhost/demo/package.zip", "http://localhost/demo/version", storeStr);
    manager->update();
//    CC_SAFE_DELETE(manager);
}

void TestMultiAssetsManager::onExit()
{
	TestBaseLayer::onExit();
	// TODO: auto generated code
}

NS_QING_END