//
//  StorageUtilsTest.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-2.
//
//

#include "StorageUtilsTest.h"
#include "StorageUtils.h"

#include <time.h>

USING_NS_QING;

bool StorageUtilsTest::init()
{
	bool bRet = false;
	do
	{
		// TODO: auto generated code
        m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

StorageUtilsTest::StorageUtilsTest()
{
	// TODO: auto generated code
}

StorageUtilsTest::~StorageUtilsTest()
{
	// TODO: auto generated code
}


void StorageUtilsTest::onEnter()
{
	TestBaseLayer::onEnter();
    
    CCLabelTTF* lbl = CCLabelTTF::create("", FONT_NAME, FONT_SIZE);
    lbl->setPosition(VisibleRect::center());
    addChild(lbl);
    
    StorageUtils::shared()->show();
    
    
    StorageUtils::shared()->set("boolTest", true);
    StorageUtils::shared()->set("intTest", 123);
    StorageUtils::shared()->set("floatTest", 3.14f);
    StorageUtils::shared()->set("doubleTest",1334343423.123456789);
    string name = "Kevin";
    StorageUtils::shared()->setString("nameTest", name);
    
    CCLOG("Name from Storage : %s", StorageUtils::shared()->getString("nameTest").c_str());
    CCLOG("Name from Storage float: %f", StorageUtils::shared()->getFloat("floatTest"));
    
    string key = "lastVisitTime";
    
    string str = StorageUtils::shared()->getString(key);
    str = "上次访问时间: " + str;
    lbl->setString(str.c_str());
    
    time_t t = time(0);
    char tmp[64] ;
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A 本年第%j天 %z", localtime(&t));
    str = tmp;
    CCLOG("当前时间：%s", tmp);
    StorageUtils::shared()->setString(key, str);
    
}

void StorageUtilsTest::onExit()
{
	TestBaseLayer::onExit();
	// TODO: auto generated code
}

