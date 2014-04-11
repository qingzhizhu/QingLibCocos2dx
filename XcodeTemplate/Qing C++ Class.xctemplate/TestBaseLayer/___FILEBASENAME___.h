//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//
/// 测试的基类layer

#ifndef _____PROJECTNAMEASIDENTIFIER________FILEBASENAMEASIDENTIFIER_____
#define _____PROJECTNAMEASIDENTIFIER________FILEBASENAMEASIDENTIFIER_____

#include "Common.h"
#include "TestBaseLayer.h"

NS_QING_BEGIN


class ___FILEBASENAMEASIDENTIFIER___ : public TestBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(___FILEBASENAMEASIDENTIFIER___);
    ___FILEBASENAMEASIDENTIFIER___();
	~___FILEBASENAMEASIDENTIFIER___();
	
	virtual void onEnter();
	virtual void onExit();
};

NS_QING_END

#endif /* defined(_____PROJECTNAMEASIDENTIFIER________FILEBASENAMEASIDENTIFIER_____) */
