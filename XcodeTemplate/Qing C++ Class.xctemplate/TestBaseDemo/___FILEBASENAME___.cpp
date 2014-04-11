//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//

#include "___FILEBASENAME___.h"

USING_NS_QING;

bool ___FILEBASENAMEASIDENTIFIER___::init()
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

___FILEBASENAMEASIDENTIFIER___::___FILEBASENAMEASIDENTIFIER___()
{
	// TODO: auto generated code
}

___FILEBASENAMEASIDENTIFIER___::~___FILEBASENAMEASIDENTIFIER___()
{
	// TODO: auto generated code
}

CCLayer* ___FILEBASENAMEASIDENTIFIER___::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
	// TODO: auto generated code
	switch (m_nLayerIndex) {
        case 0:
            
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

