//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//
/// 底部带回退，重置，前进按钮

#ifndef _____PROJECTNAMEASIDENTIFIER________FILEBASENAMEASIDENTIFIER_____
#define _____PROJECTNAMEASIDENTIFIER________FILEBASENAMEASIDENTIFIER_____

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN


class ___FILEBASENAMEASIDENTIFIER___ : public TestBaseDemo
{
public:
	virtual bool init();
	CREATE_FUNC(___FILEBASENAMEASIDENTIFIER___);
	___FILEBASENAMEASIDENTIFIER___();
	virtual ~___FILEBASENAMEASIDENTIFIER___();

	/**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 1; }
};

NS_QING_END

#endif /* defined(_____PROJECTNAMEASIDENTIFIER________FILEBASENAMEASIDENTIFIER_____) */
