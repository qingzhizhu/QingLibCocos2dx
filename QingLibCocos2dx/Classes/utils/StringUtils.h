//
//  StringUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-11.
//
//

#ifndef __QingLibCocos2dx__StringUtils__
#define __QingLibCocos2dx__StringUtils__

#include "Common.h"

NS_QING_BEGIN


class StringUtils
{
public:
    StringUtils();
	~StringUtils();
    
    /**替换*/
    static string& replaceAll(string& src, const string& oldStr, const string& newStr);
    
    
    
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__StringUtils__) */
