//
//  MyAssetsManager.h
//  QingLibCocos2dxLua
//
//  Created by Kevin Geng on 14-3-12.
//
//
/// 此类是AssetsManager的封转类，帮助下载和解压远程资源

#ifndef __QingLibCocos2dxLua__MyAssetsManager__
#define __QingLibCocos2dxLua__MyAssetsManager__

#include "Common.h"

NS_QING_BEGIN


class MyAssetsManager : public AssetsManagerDelegateProtocol
{
private:
    MyAssetsManager();
	virtual ~MyAssetsManager();
    
public:
    /**
     * 设置下载路径和版本路径，成功后调用函调函数
     *
     */
    MyAssetsManager(string packageUrl, string versionUrl, CCObject* callbackTarget, SEL_CallFunc callbackFun);
    
#pragma mark -
    /* @brief Call back function for error
     @param errorCode Type of error
     */
    virtual void onError(AssetsManager::ErrorCode errorCode);
    /** @brief Call back function for recording downloading percent
     @param percent How much percent downloaded
     @warn This call back function just for recording downloading percent.
     AssetsManager will do some other thing after downloading, you should
     write code in onSuccess() after downloading.
     */
    virtual void onProgress(int percent);
    /** @brief Call back function for success
     */
    virtual void onSuccess();
#pragma mark -
    
    /**设置搜索的资源路径, 将下载的路径放在搜索的范围*/
    void setSearchPaths();
    
    /**开始下载资源*/
    void startDownload();
    
    /**删除下载内容*/
    void removeDownload();
    
protected:
    
    void init();
    
    /***/
    AssetsManager* getAssetsManager();
    
    /**创建下载目录*/
    void createDownloadedDir();
    
    void callBack();
    
protected:
    
    /**是否下载过*/
    bool m_bIsUpdated;
    
    /**保存的路径*/
    string m_sPathToSave;
    
    CCObject* m_pCallbackTarget;
    SEL_CallFunc m_pCallbackFun;
    
#pragma mark -getter & setter
    
    /**百分比*/
    CC_SYNTHESIZE_READONLY(int, m_nPercent, Percent);
    
    /**检查是否成功下载*/
    CC_SYNTHESIZE_READONLY(bool, m_bIsSuccessed, IsSuccessed);
    
    /**是否有错误*/
    CC_SYNTHESIZE_READONLY(int, m_nErrorCode, ErrorCode);
    
    /**下载需要的资源包url和版本url*/
    CC_SYNTHESIZE(string, m_sPackageUrl, PackageUrl);
    CC_SYNTHESIZE(string, m_sVersionUrl, VersionUrl);
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dxLua__MyAssetsManager__) */
