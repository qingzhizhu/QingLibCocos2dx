//
//  TestMultiAssetsManager.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-25.
//
//
/// 测试的基类layer

#ifndef __QingLibCocos2dx__TestMultiAssetsManager__
#define __QingLibCocos2dx__TestMultiAssetsManager__

#include "Common.h"
#include "TestBaseLayer.h"
#include "MultiAssetsManager.h"

NS_QING_BEGIN

// 直接是一个delegate
class TestMultiAssetsManager : public TestBaseLayer
, public MultiAssetsManager::MultiAssetsManagerDelegateProtocol
{
public:
	virtual bool init();
	CREATE_FUNC(TestMultiAssetsManager);
    TestMultiAssetsManager();
	~TestMultiAssetsManager();
	
	virtual void onEnter();
	virtual void onExit();
    
    void setCallback(CCObject *callbackTarget, SEL_CallFunc callbackFun);
    
    /**外部的函数*/
    void onSuccessTest();
    
public:
    /* @brief Call back function for error
     @param errorCode Type of error
     */
    virtual void onError(MultiAssetsManager::ErrorCode errorCode);
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
    
    
protected:
    
    MultiAssetsManager *m_pManager;
    
    void callBack();
    
    CCObject* m_pCallbackTarget;
    SEL_CallFunc m_pCallbackFun;
    
#pragma mark -getter & setter
    
    /**百分比*/
    CC_SYNTHESIZE_READONLY(int, m_nPercent, Percent);
    
    /**检查是否成功下载*/
    CC_SYNTHESIZE_READONLY(bool, m_bIsSuccessed, IsSuccessed);
    
    /**是否有错误*/
    CC_SYNTHESIZE_READONLY(int, m_nErrorCode, ErrorCode);
    
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestMultiAssetsManager__) */ 
