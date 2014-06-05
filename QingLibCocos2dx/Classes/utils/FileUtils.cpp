//
//  FileUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-5.
//
//

#include "FileUtils.h"	

USING_NS_QING;

/*
static FileUtils* s_sharedFileUtils = NULL;

FileUtils* FileUtils::shared(void)
{
	if (!s_sharedFileUtils)
	{
		s_sharedFileUtils = new FileUtils();
	}
	return s_sharedFileUtils;
}

void FileUtils::purge()
{
//	CC_SAFE_RELEASE_NULL(s_sharedFileUtils);
    delete s_sharedFileUtils;
    s_sharedFileUtils = 0;
}
*/

FileUtils::FileUtils()
{
    
}

FileUtils::~FileUtils()
{
    
}


string FileUtils::fullPathForFilename(const char *fileName)
{
    return CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
}


string FileUtils::getWritablePath(const char *fileName)
{
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    return path.append(fileName);
}




void FileUtils::getPathByType(string &path, QingCocos2dx::FILE_PATH_TYPE pathType)
{
    switch (pathType) {
        case FILE_PATH_TYPE_FULLPATH:
            path = fullPathForFilename(path.c_str());
            break;
        case FILE_PATH_TYPE_WRITABLE:
            path = getWritablePath(path.c_str());
            break;
            
        default:
            break;
    }
}



bool FileUtils::save(string &path, string &data, FILE_PATH_TYPE pathType)
{
    getPathByType(path, pathType);
    CCLOG("save file path: %s", path.c_str());
    FILE* file = fopen(path.c_str(), "w");
    if(file){
        fwrite(data.c_str(), 1, data.length(), file);
        fclose(file);
        CCLOG("save successful!");
        return true;
    }
    CCLOG("save error!");
    return false;
}


bool FileUtils::loadFile(string &path, string &strResult, FILE_PATH_TYPE pathType)
{
    getPathByType(path, pathType);
    CCLOG("loadFile path:%s", path.c_str());
    unsigned long size = 0;
    char* pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &size);
    if(pBuffer != NULL && size > 0){
        strResult.clear();
        strResult.append(pBuffer, size);
        CC_SAFE_DELETE_ARRAY(pBuffer);
        return true;
    }
    CCLog("open error:%s", path.c_str());
    return false;
}














