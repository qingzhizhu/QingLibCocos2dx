//
//  AssetsManagerDemo.h
//  QingLibCocos2dxLua
//
//  Created by Kevin Geng on 14-3-13.
//
//

#ifndef __QingLibCocos2dxLua__AssetsManagerDemo__
#define __QingLibCocos2dxLua__AssetsManagerDemo__

#include "Common.h"

NS_QING_BEGIN


class AssetsManagerDemo : public CCLayer
{
public:
    static CCScene * scene();
    
    AssetsManagerDemo();
	~AssetsManagerDemo();
    
    static void runLua();
    
protected:
    void callBack();
};

NS_QING_END

#endif /* defined(__QingLibCocos2dxLua__AssetsManagerDemo__) */
