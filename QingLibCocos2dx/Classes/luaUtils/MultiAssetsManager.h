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

#pragma mark  ------------------------ 平台差异资源前缀 ---------------------

#define MULTIASSETSMANAGER_ASSETS_ANDROID   "_a_"
#define MULTIASSETSMANAGER_ASSETS_IOS       "_i_"


#pragma mark  ------------------------ 下载阶段 ---------------------

//enum MULTIASSETSMANAGER_STAGE {
//    MULTIASSETSMANAGER_STAGE_NONE,
//    /**正在下载中*/
//    MULTIASSETSMANAGER_STAGE_DOWNLOADING,
//    /**下载完成*/
//    MULTIASSETSMANAGER_STAGE_DOWNLOADED,
//    /**临时下载文件拷贝到资源storage*/
//    MULTIASSETSMANAGER_STAGE_TEMP_COPY,
//    /**完成*/
//    MULTIASSETSMANAGER_STAGE_OVER
//};

#pragma mark-



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
    
    class MultiAssetsManagerDelegateProtocol
    {
    public:
        /* @brief Call back function for error
         @param errorCode Type of error
         */
        virtual void onError(ErrorCode errorCode) { };
        /** @brief Call back function for recording downloading percent
         @param percent How much percent downloaded
         @warn This call back function just for recording downloading percent.
         AssetsManager will do some other thing after downloading, you should
         write code in onSuccess() after downloading.
         */
        virtual void onProgress(int percent) { };
        /** @brief Call back function for success
         */
        virtual void onSuccess() { };
    };
    
    
    /**
     * @param assetsServerUrl 资源服务器url
     * @param packagePrefix 资源包前缀
     * @param versionFileName 版本文件名称
     * @param storagePath 保存路径
     * @param useAssetsPlatform 是否使用平台差异资源前缀
     */
    MultiAssetsManager(string assetsServerUrl="http://localhost/demo/", string packagePrefix="package", string versionFileName="version", string storagePath = ".Elextech_RAM/", bool useAssetsPlatform=false);
    
    
    virtual ~MultiAssetsManager();
    
    void setSearchPath();
    
    /**删除所有下载内容*/
    void removeDownload();
    void removeDownloadByPath(string path);
    
    /* @brief Deletes recorded version code.
     */
    void deleteVersion();
    
#pragma mark  ------------------------ getter & setter ---------------------    
    /**正在下载的版本号*/
    int getDownloadVersionIdx() { return _nDownloadVersion - _nLocalVersion; }
    
    /**需要下载的版本数量*/
    int getDownloadVersionNum() { return _nTotalVersion - _nLocalVersion; }
    
    /**是否下载完成*/
    bool needDownload() { return _nDownloadVersion < _nTotalVersion; }
    
    /* @brief Gets url of package.
     */
    const char* getPackageUrl() const;
    
    /* @brief Gets version file url.
     */
    const char* getVersionFileUrl() const;
    
    /* @brief Gets version file url.
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief Gets current version code.
     */
    std::string getVersion();
    
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
    void setDelegate(MultiAssetsManagerDelegateProtocol *delegate);
    
    //    MultiAssetsManagerDelegate *getDelegate() { return _schedule; }
    
    /** @brief Sets connection time out in seconds
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief Gets connection time out in secondes
     */
    unsigned int getConnectionTimeout();
    
    
#pragma mark  ------------------------ download ---------------------
    
    /**
     * 开始下载资源
     * @param callbackTarget 
     * @param callbackFun 回调函数
     * @param delegate 默认使用自己的
     */
    void startDownload(MultiAssetsManagerDelegateProtocol *delegate);
    
    /* @brief Download new package if there is a new version, and uncompress downloaded zip file.
     *        Ofcourse it will set search path that stores downloaded files.
     */
    virtual void update();
    
    /* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual bool checkUpdate();
    
    
    
    /**
     * 同步临时文件到资源文件中
     */
    bool synchTempDir();
    
    
    /* downloadAndUncompress is the entry of a new thread
     */
    friend void* assetsManagerDownloadAndUncompress(void*);
    friend int assetsManagerProgressFunc(void *, double, double, double, double);
    
protected:
    void checkStoragePath();
    
    bool createDirectorys();
    bool createDirectory(string path);
    
    //-------- download ----------
    bool downLoad();
    bool uncompress();
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
    /**string 获得下一个版本号*/
    string getDownloadVersion();
    
    string _assetsServerUrl;
    string _packagePerfix;
    string _versionFileName;
    
    uint _nLocalVersion;
    uint _nTotalVersion;
    /**下载的下标*/
    uint _nDownloadVersion;
    
    /**临时保存文件夹*/
    string _tempStoragePath;
    /**临时文件中的所有路径*/
    vector<string> _arrTempFilePaths;
    
    
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
    /**请求超时时间，默认300s.*/
    unsigned int _connectionTimeout;
    
    MultiAssetsManagerDelegateProtocol *_delegate; // weak reference
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__MultiAssetsManager__) */
