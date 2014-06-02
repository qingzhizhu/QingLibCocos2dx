//
//  StorageUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-2.
//
//

#include "StorageUtils.h"	
#include "CCUserDefault.h"

USING_NS_QING;

static StorageUtils* s_sharedStorageUtils = NULL;

StorageUtils* StorageUtils::shared(void)
{
	if (!s_sharedStorageUtils)
	{
		s_sharedStorageUtils = new StorageUtils();
	}
	return s_sharedStorageUtils;
}

void StorageUtils::purge()
{
//	CC_SAFE_RELEASE_NULL(s_sharedStorageUtils);
    delete s_sharedStorageUtils;
    s_sharedStorageUtils = 0;
}

StorageUtils::StorageUtils()
{
	
}

StorageUtils::~StorageUtils()
{
	
}


static CCUserDefault* getStorage()
{
    return CCUserDefault::sharedUserDefault();
}


void StorageUtils::show()
{
    if(CCUserDefault::isXMLFileExist()){
        CCLOG("Storage XML: %s", CCUserDefault::getXMLFilePath().c_str());
    }else{
        CCLOG("不存在Storage XML！");
    }
}

void StorageUtils::flush()
{
    getStorage()->flush();
}


void StorageUtils::set(string key, bool value)
{
    getStorage()->setBoolForKey(key.c_str(), value);
    flush();
}

bool StorageUtils::getBool(string key, bool value)
{
    return getStorage()->getBoolForKey(key.c_str(), value);
}


void StorageUtils::set(string key, int value)
{
    getStorage()->setIntegerForKey(key.c_str(), value);
    flush();
}

int StorageUtils::getInt(string key, int value)
{
    return getStorage()->getIntegerForKey(key.c_str(), value);
}


void StorageUtils::set(string key, float value)
{
    getStorage()->setFloatForKey(key.c_str(), value);
    flush();
}

float StorageUtils::getFloat(string key, float value)
{
    return getStorage()->getFloatForKey(key.c_str(), value);
}


void StorageUtils::set(string key, double value)
{
    getStorage()->setDoubleForKey(key.c_str(), value);
    flush();
}

double StorageUtils::getDouble(string key, double value)
{
    return getStorage()->getDoubleForKey(key.c_str(), value);
}


void StorageUtils::setString(string key, string &value)
{
    getStorage()->setStringForKey(key.c_str(), value);
    flush();
}

string StorageUtils::getString(string key, string value)
{
    return getStorage()->getStringForKey(key.c_str(), value);
}



