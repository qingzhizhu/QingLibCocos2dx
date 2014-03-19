//
//  MyAssetsManagerDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-3-19.
//
//

#ifndef __QingLibCocos2dx__MyAssetsManagerDemo__
#define __QingLibCocos2dx__MyAssetsManagerDemo__

#include "Common.h"
#include "TestBaseLayer.h"

NS_QING_BEGIN


class MyAssetsManagerDemo : public TestBaseLayer
{
public:
    MyAssetsManagerDemo();
    CREATE_FUNC(MyAssetsManagerDemo);
	~MyAssetsManagerDemo();
protected:
    virtual void callBack();
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__MyAssetsManagerDemo__) */
