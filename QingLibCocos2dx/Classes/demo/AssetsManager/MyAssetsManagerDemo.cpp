//
//  MyAssetsManagerDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-3-19.
//
//

#include "MyAssetsManagerDemo.h"
#include "MyAssetsManager.h"


USING_NS_QING;

static MyAssetsManager* manager;
MyAssetsManagerDemo::MyAssetsManagerDemo()
{
    manager = new MyAssetsManager("http://localhost/demo/package.zip", "http://localhost/demo/version", this, callfunc_selector(MyAssetsManagerDemo::callBack));
//    manager->removeDownload();        //若主动删除文件内容，version信息不会更新
    manager->startDownload();
}

MyAssetsManagerDemo::~MyAssetsManagerDemo()
{
	// TODO: auto generated code
}

void MyAssetsManagerDemo::callBack()
{
    CCLOG("更新完毕！");
    if(!manager->getIsSuccessed()) return;
    
    CCSprite* img = CCSprite::create("1_s.png");
    img->cocos2d::CCNode::setPosition(200, 300);
    addChild(img);
    
}


