//
//  MultiAssetsManager.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-25.
//
//

#include "MultiAssetsManager.h"
#include "cocos2d.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <vector>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#endif

#include "support/zip_support/unzip.h"

//USING_NS_QING;
NS_QING_BEGIN

#define KEY_OF_VERSION   "current-version-code"
#define KEY_OF_DOWNLOADED_VERSION    "downloaded-version-code"
#define TEMP_PACKAGE_FILE_NAME    "cocos2dx-update-temp-package.zip"
#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

// Message type
#define MultiAssetsManager_MESSAGE_UPDATE_SUCCEED                0
#define MultiAssetsManager_MESSAGE_RECORD_DOWNLOADED_VERSION     1
#define MultiAssetsManager_MESSAGE_PROGRESS                      2
#define MultiAssetsManager_MESSAGE_ERROR                         3

// Some data struct for sending messages

struct ErrorMessage
{
    MultiAssetsManager::ErrorCode code;
    MultiAssetsManager* manager;
};

struct ProgressMessage
{
    int percent;
    MultiAssetsManager* manager;
};

// Implementation of MultiAssetsManager

MultiAssetsManager::MultiAssetsManager(const char* packageUrl/* =NULL */, const char* versionFileUrl/* =NULL */, string storagePath/* =NULL */)
:  _storagePath(storagePath)
, _version("")
, _packageUrl(packageUrl)
, _versionFileUrl(versionFileUrl)
, _downloadedVersion("")
, _curl(NULL)
, _tid(NULL)
, _connectionTimeout(0)
, _delegate(NULL)
{
    checkStoragePath();
    _schedule = new Helper();
}

MultiAssetsManager::~MultiAssetsManager()
{
    CC_SAFE_DELETE(_schedule);
}

void MultiAssetsManager::checkStoragePath()
{
    if (_storagePath.size() > 0 && _storagePath[_storagePath.size() - 1] != '/')
    {
        _storagePath.append("/");
    }
}

static size_t getVersionCode(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *version = (string*)userdata;
    version->append((char*)ptr, size * nmemb);
    
    return (size * nmemb);
}

bool MultiAssetsManager::checkUpdate()
{
    CCLOG("[MultiAssetsManager] 1 checkUpdate");
    if (_versionFileUrl.size() == 0) return false;
    
    _curl = curl_easy_init();
    if (! _curl)
    {
        CCLOG("can not init curl");
        return false;
    }
    
    // Clear _version before assign new value.
    _version.clear();
    
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, _versionFileUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getVersionCode);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_version);
    if (_connectionTimeout) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
    res = curl_easy_perform(_curl);
    
    if (res != 0)
    {
        sendErrorMessage(kNetwork);
        CCLOG("can not get version file content, error code is %d", res);
        curl_easy_cleanup(_curl);
        return false;
    }
    
    string recordedVersion = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_OF_VERSION);
    if (recordedVersion == _version)
    {
        sendErrorMessage(kNoNewVersion);
        CCLOG("there is not new version");
        // Set resource search path.
        setSearchPath();
        return false;
    }
    
    CCLOG("there is a new version: %s", _version.c_str());
    
    return true;
}

void* assetsManagerDownloadAndUncompress(void *data)
{
    CCLOG("[MultiAssetsManager] 2 assetsManagerDownloadAndUncompress");
    MultiAssetsManager* self = (MultiAssetsManager*)data;
    
    do
    {
        if (self->_downloadedVersion != self->_version)
        {
            if (! self->downLoad()) break;
            
            // Record downloaded version.
            MultiAssetsManager::Message *msg1 = new MultiAssetsManager::Message();
            msg1->what = MultiAssetsManager_MESSAGE_RECORD_DOWNLOADED_VERSION;
            msg1->obj = self;
            self->_schedule->sendMessage(msg1);
        }
        
        // Uncompress zip file.
        if (! self->uncompress())
        {
            self->sendErrorMessage(MultiAssetsManager::kUncompress);
            break;
        }
        
        // Record updated version and remove downloaded zip file
        MultiAssetsManager::Message *msg2 = new MultiAssetsManager::Message();
        msg2->what = MultiAssetsManager_MESSAGE_UPDATE_SUCCEED;
        msg2->obj = self;
        self->_schedule->sendMessage(msg2);
    } while (0);
    
    if (self->_tid)
    {
        delete self->_tid;
        self->_tid = NULL;
    }
    
    return NULL;
}

void MultiAssetsManager::update()
{
    CCLOG("[MultiAssetsManager] 0 update");
    if (_tid) return;
    
    // 1. Urls of package and version should be valid;
    // 2. Package should be a zip file.
    if (_versionFileUrl.size() == 0 ||
        _packageUrl.size() == 0 ||
        std::string::npos == _packageUrl.find(".zip"))
    {
        CCLOG("no version file url, or no package url, or the package is not a zip file");
        return;
    }
    
    // Check if there is a new version.
    if (! checkUpdate()) return;
    
    // Is package already downloaded?
    _downloadedVersion = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_OF_DOWNLOADED_VERSION);
    
    _tid = new pthread_t();
    pthread_create(&(*_tid), NULL, assetsManagerDownloadAndUncompress, this);
}

bool MultiAssetsManager::uncompress()
{
    CCLOG("[MultiAssetsManager] 5 uncompress");
    // Open the zip file
    string outFileName = _storagePath + TEMP_PACKAGE_FILE_NAME;     //TODO: 加上版本号
    unzFile zipfile = unzOpen(outFileName.c_str());
    if (! zipfile)
    {
        CCLOG("can not open downloaded zip file %s", outFileName.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("can not read file global info of %s", outFileName.c_str());
        unzClose(zipfile);
        return false;
    }
    
    // Buffer to hold data read from the zip file
    char readBuffer[BUFFER_SIZE];
    
    CCLOG("start uncompressing");
    
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  NULL,
                                  0,
                                  NULL,
                                  0) != UNZ_OK)
        {
            CCLOG("can not read file info");
            unzClose(zipfile);
            return false;
        }
        
        string fullPath = _storagePath + fileName;
        //TODO: Need md5 Check!
        
        // Check if this entry is a directory or a file.
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] == '/')
        {
            // Entry is a direcotry, so create it.
            // If the directory exists, it will failed scilently.
            if (!createDirectory(fullPath.c_str()))
            {
                CCLOG("can not create directory %s", fullPath.c_str());
                unzClose(zipfile);
                return false;
            }
        }
        else
        {
            // Entry is a file, so extract it.
            
            // Open current file.
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not open file %s", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(fullPath.c_str(), "wb");
            if (! out)
            {
                CCLOG("can not open destination file %s", fullPath.c_str());
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }
            
            // Write current file content to destinate file.
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
                if (error < 0)
                {
                    CCLOG("can not read zip file %s, error code is %d", fileName, error);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }
                
                if (error > 0)
                {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);
            
            fclose(out);
        }
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not read next file");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    CCLOG("end uncompressing");
    
    return true;
}

/*
 * Create a direcotry is platform depended.
 */
bool MultiAssetsManager::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    mode_t processMask = umask(0);
    int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    
    return true;
#else
    BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
    return true;
#endif
}

void MultiAssetsManager::setSearchPath()
{
    vector<string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
    vector<string>::iterator iter = searchPaths.begin();
    searchPaths.insert(iter, _storagePath);
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
}

static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    CCLOG("[MultiAssetsManager] downLoadPackage");
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

int assetsManagerProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    CCLOG("[MultiAssetsManager] 4+ assetsManagerProgressFunc");
    MultiAssetsManager* manager = (MultiAssetsManager*)ptr;
    MultiAssetsManager::Message *msg = new MultiAssetsManager::Message();
    msg->what = MultiAssetsManager_MESSAGE_PROGRESS;
    
    ProgressMessage *progressData = new ProgressMessage();
    progressData->percent = (int)(nowDownloaded/totalToDownload*100);
    progressData->manager = manager;
    msg->obj = progressData;
    
    manager->_schedule->sendMessage(msg);
    
    CCLOG("downloading... %d%%", (int)(nowDownloaded/totalToDownload*100));
    
    return 0;
}

bool MultiAssetsManager::downLoad()
{
    CCLOG("[MultiAssetsManager] 3 downLoad");
    // Create a file to save package.
    string outFileName = _storagePath + TEMP_PACKAGE_FILE_NAME;
    FILE *fp = fopen(outFileName.c_str(), "wb");
    if (! fp)
    {
        sendErrorMessage(kCreateFile);
        CCLOG("can not create file %s", outFileName.c_str());
        return false;
    }
    
    // Download pacakge
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, _packageUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downLoadPackage);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, assetsManagerProgressFunc);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res != 0)
    {
        sendErrorMessage(kNetwork);
        CCLOG("error when download package");
        fclose(fp);
        return false;
    }
    
    CCLOG("succeed downloading package %s", _packageUrl.c_str());
    
    fclose(fp);
    return true;
}

const char* MultiAssetsManager::getPackageUrl() const
{
    return _packageUrl.c_str();
}

void MultiAssetsManager::setPackageUrl(const char *packageUrl)
{
    _packageUrl = packageUrl;
}

const char* MultiAssetsManager::getStoragePath() const
{
    return _storagePath.c_str();
}

void MultiAssetsManager::setStoragePath(const char *storagePath)
{
    _storagePath = storagePath;
    checkStoragePath();
}

const char* MultiAssetsManager::getVersionFileUrl() const
{
    return _versionFileUrl.c_str();
}

void MultiAssetsManager::setVersionFileUrl(const char *versionFileUrl)
{
    _versionFileUrl = versionFileUrl;
}

string MultiAssetsManager::getVersion()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey(KEY_OF_VERSION);
}

void MultiAssetsManager::deleteVersion()
{
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_VERSION, "");
}

void MultiAssetsManager::setDelegate(MultiAssetsManagerDelegate *delegate)
{
    _delegate = delegate;
}

void MultiAssetsManager::setConnectionTimeout(unsigned int timeout)
{
    _connectionTimeout = timeout;
}

unsigned int MultiAssetsManager::getConnectionTimeout()
{
    return _connectionTimeout;
}

void MultiAssetsManager::sendErrorMessage(MultiAssetsManager::ErrorCode code)
{
    Message *msg = new Message();
    msg->what = MultiAssetsManager_MESSAGE_ERROR;
    
    ErrorMessage *errorMessage = new ErrorMessage();
    errorMessage->code = code;
    errorMessage->manager = this;
    msg->obj = errorMessage;
    
    _schedule->sendMessage(msg);
}

// Implementation of MultiAssetsManagerHelper

MultiAssetsManager::Helper::Helper()
{
    _messageQueue = new list<Message*>();
    pthread_mutex_init(&_messageQueueMutex, NULL);
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

MultiAssetsManager::Helper::~Helper()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    delete _messageQueue;
}

void MultiAssetsManager::Helper::sendMessage(Message *msg)
{
    pthread_mutex_lock(&_messageQueueMutex);
    _messageQueue->push_back(msg);
    pthread_mutex_unlock(&_messageQueueMutex);
}

void MultiAssetsManager::Helper::update(float dt)
{
    CCLOG("[MultiAssetsManager] Helpe::update");
    Message *msg = NULL;
    
    // Returns quickly if no message
    pthread_mutex_lock(&_messageQueueMutex);
    if (0 == _messageQueue->size())
    {
        pthread_mutex_unlock(&_messageQueueMutex);
        return;
    }
    
    // Gets message
    msg = *(_messageQueue->begin());
    _messageQueue->pop_front();
    pthread_mutex_unlock(&_messageQueueMutex);
    
    switch (msg->what) {
        case MultiAssetsManager_MESSAGE_UPDATE_SUCCEED:
            CCLOG("[MultiAssetsManager] last MESSAGE_UPDATE_SUCCEED");
            handleUpdateSucceed(msg);
            
            break;
        case MultiAssetsManager_MESSAGE_RECORD_DOWNLOADED_VERSION:
            CCLOG("[MultiAssetsManager] last MESSAGE_RECORD_DOWNLOADED_VERSION");
            CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_DOWNLOADED_VERSION,
                                                                ((MultiAssetsManager*)msg->obj)->_version.c_str());
            CCUserDefault::sharedUserDefault()->flush();
            
            break;
        case MultiAssetsManager_MESSAGE_PROGRESS:
            if (((ProgressMessage*)msg->obj)->manager->_delegate)
            {
                ((ProgressMessage*)msg->obj)->manager->_delegate->onProgress(((ProgressMessage*)msg->obj)->percent);
            }
            
            delete (ProgressMessage*)msg->obj;
            
            break;
        case MultiAssetsManager_MESSAGE_ERROR:
            // error call back
            if (((ErrorMessage*)msg->obj)->manager->_delegate)
            {
                ((ErrorMessage*)msg->obj)->manager->_delegate->onError(((ErrorMessage*)msg->obj)->code);
            }
            
            delete ((ErrorMessage*)msg->obj);
            
            break;
        default:
            break;
    }
    
    delete msg;
}

void MultiAssetsManager::Helper::handleUpdateSucceed(Message *msg)
{
    CCLOG("[MultiAssetsManager] Helper::handleUpdateSucceed");
    MultiAssetsManager* manager = (MultiAssetsManager*)msg->obj;
    
    // Record new version code.
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_VERSION, manager->_version.c_str());
    
    // Unrecord downloaded version code.
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_DOWNLOADED_VERSION, "");
    CCUserDefault::sharedUserDefault()->flush();
    
    // Set resource search path.
    manager->setSearchPath();
    
    // Delete unloaded zip file.
    string zipfileName = manager->_storagePath + TEMP_PACKAGE_FILE_NAME;
    if (remove(zipfileName.c_str()) != 0)
    {
        CCLOG("can not remove downloaded zip file %s", zipfileName.c_str());
    }
    
    if (manager) manager->_delegate->onSuccess();
}

NS_QING_END