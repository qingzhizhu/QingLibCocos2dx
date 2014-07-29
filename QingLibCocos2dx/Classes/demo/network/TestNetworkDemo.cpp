//
//  TestNetworkDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-7-28.
//
//

#include "TestNetworkDemo.h"
#include "FileUtils.h"

#include "curl/curl.h"
#include "curl/easy.h"


NS_QING_BEGIN

bool TestNetworkDemo::init()
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

TestNetworkDemo::TestNetworkDemo()
{
	
}

TestNetworkDemo::~TestNetworkDemo()
{
	
}



static size_t downloadPage(void *prt, size_t size, size_t nmemb, void *userdata)
{
    FILE *fp = (FILE*)userdata;
    size_t writable = fwrite(prt, size, nmemb, fp);
    CCLOG("writable=%lu, size * nmemb = %lu", writable, size * nmemb);
    return writable;
}


int onProgress(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    TestNetworkDemo *self = (TestNetworkDemo*)ptr;
    CCLOG("self %p", self);
    int percent = totalToDownload == 0 ? 0 : (nowDownloaded / totalToDownload * 100);
    CCLOG("progress %d%%", percent);
    
    return 0;
}


CCLayer* TestNetworkDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
	
	switch (m_nLayerIndex) {
        case 0:{
            setTitle("CURL 访问主页html，保存到本地");
            string str = "";
            
            FILE *fp = fopen(FileUtils::getWritablePath("MyHome.html").c_str(), "wb");
            
            
            CURL *curl = curl_easy_init();
            if(curl){
                curl_easy_setopt(curl, CURLOPT_URL, "http://qingzhizhu.github.io/");
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadPage);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);  //默认true
                curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, onProgress);
                curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
                
                CURLcode code = curl_easy_perform(curl);
                if(code == CURLE_OK){
                    
                }else{
                    str += "网络异常,";
                }
                
            }else{
                str += "CURL init failed!";
            }
            fclose(fp);
            createLabel(layer, str.c_str());
        }
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

NS_QING_END