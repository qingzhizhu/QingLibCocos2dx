//
//  MultiAssetsManager.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-25.
//
//
// 差异下载

#ifndef __QingLibCocos2dx__MultiAssetsManager__
#define __QingLibCocos2dx__MultiAssetsManager__

#include "Common.h"

#include <string>
#include <curl/curl.h>
#include <pthread.h>

#include "cocos2d.h"
#include "ExtensionMacros.h"


NS_QING_BEGIN


class MultiAssetsManager
{
public:
    enum ErrorCode
    {
        // Error caused by creating a file to store downloaded data
        kCreateFile,
        /** Error caused by network
         -- network unavaivable
         -- timeout
         -- ...
         */
        kNetwork,
        /** There is not a new version
         */
        kNoNewVersion,
        /** Error caused in uncompressing stage
         -- can not open zip file
         -- can not read file global information
         -- can not read file information
         -- can not create a directory
         -- ...
         */
        kUncompress,
    };
    
//    class MultiAssetsManagerDelegate
//    {
//    public:
//        void onDownload(string packUrl);
//        void onUncompress(string packUrl);
//        void onError(ErrorCode errorCode);
//        void onProgress(int percent, int type = 1);
//        void onSuccess();
//    };
    
    class MultiAssetsManagerDelegate
    {
    public:
        /* @brief Call back function for error
         @param errorCode Type of error
         */
        virtual void onError(ErrorCode errorCode) {};
        /** @brief Call back function for recording downloading percent
         @param percent How much percent downloaded
         @warn This call back function just for recording downloading percent.
         AssetsManager will do some other thing after downloading, you should
         write code in onSuccess() after downloading.
         */
        virtual void onProgress(int percent) {};
        /** @brief Call back function for success
         */
        virtual void onSuccess() {};
    };
    
    /* @brief Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @param packageUrl URL of new package, the package should be a zip file.
     * @param versionFileUrl URL of version file. It should contain version code of new package.
     * @param storagePath The path to store downloaded resources.
     */
    MultiAssetsManager(const char* packageUrl = NULL, const char* versionFileUrl = NULL, string storagePath = NULL);
    
    virtual ~MultiAssetsManager();
    
    /* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual bool checkUpdate();
    
    /* @brief Download new package if there is a new version, and uncompress downloaded zip file.
     *        Ofcourse it will set search path that stores downloaded files.
     */
    virtual void update();
    
    /* @brief Gets url of package.
     */
    const char* getPackageUrl() const;
    
    /* @brief Sets package url.
     */
    void setPackageUrl(const char* packageUrl);
    
    /* @brief Gets version file url.
     */
    const char* getVersionFileUrl() const;
    
    /* @brief Gets version file url.
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief Gets current version code.
     */
    std::string getVersion();
    
    /* @brief Deletes recorded version code.
     */
    void deleteVersion();
    
    /* @brief Gets storage path.
     */
    const char* getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    void setStoragePath(const char* storagePath);
    
    /** @brief Sets delegate, the delegate will receive messages
     */
    void setDelegate(MultiAssetsManagerDelegate *delegate);
    
//    MultiAssetsManagerDelegate *getDelegate() { return _schedule; }
    
    /** @brief Sets connection time out in seconds
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief Gets connection time out in secondes
     */
    unsigned int getConnectionTimeout();
    
    /* downloadAndUncompress is the entry of a new thread
     */
    friend void* assetsManagerDownloadAndUncompress(void*);
    friend int assetsManagerProgressFunc(void *, double, double, double, double);
    
protected:
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    bool createDirectory(const char *path);
    void setSearchPath();
    void sendErrorMessage(ErrorCode code);
    
private:
    typedef struct _Message
    {
    public:
        _Message() : what(0), obj(NULL){}
        unsigned int what; // message type
        void* obj;
    } Message;
    
    class Helper : public cocos2d::CCObject
    {
    public:
        Helper();
        ~Helper();
        
        virtual void update(float dt);
        void sendMessage(Message *msg);
        
    private:
        void handleUpdateSucceed(Message *msg);
        
        std::list<Message*> *_messageQueue;
        pthread_mutex_t _messageQueueMutex;
    };
    
private:
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The version of downloaded resources.
    std::string _version;
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    std::string _downloadedVersion;
    
    CURL *_curl;
    Helper *_schedule;
    pthread_t *_tid;
    unsigned int _connectionTimeout;
    
    MultiAssetsManagerDelegate *_delegate; // weak reference
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__MultiAssetsManager__) */
