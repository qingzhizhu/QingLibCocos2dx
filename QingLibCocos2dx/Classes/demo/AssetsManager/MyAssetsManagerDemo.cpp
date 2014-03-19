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
    manager = new MyAssetsManager("http://10.1.21.16:8099/demo/package.zip", "http://10.1.21.16:8099/demo/version", this, callfunc_selector(MyAssetsManagerDemo::callBack));
    manager->removeDownload();        //若主动删除文件内容，version信息不会更新
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
    CCSprite* img = CCSprite::create("I_9.png");
    img->cocos2d::CCNode::setPosition(200, 300);
    addChild(img);
    img = CCSprite::create("I_06.png");
    img->cocos2d::CCNode::setPosition(100, 100);
    addChild(img);
    
    img = CCSprite::create("I_15.png");
    img->cocos2d::CCNode::setPosition(200, 200);
    addChild(img);
    
}


