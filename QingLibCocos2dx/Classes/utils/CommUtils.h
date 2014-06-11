//
//  CommUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-11.
//
//

#ifndef __QingLibCocos2dx__CommUtils__
#define __QingLibCocos2dx__CommUtils__

#include "Common.h"

NS_QING_BEGIN


class CommUtils
{
public:
    CommUtils();
	~CommUtils();
    
    
    static uint getColor(unsigned char r, unsigned char g, unsigned char b);
    
    /**
     * 获取颜色R,G,B
     * @param ret [0] = R, [1] = G, [2] = B.
     */
    static void getRGB(uint color, int* ret);
    
    
#pragma mark- 正则
    
    /**
     * 是否是邮件格式
     * 用到了正则，windows 下不支持
     */
    static bool isEmail(string& str);
    
    
    /**
     * 是否是密码格式
     * 密码由8-16位字母、数字和下划线组成
     */
    static bool isPassword(string& str);
    
    
#pragma mark-
    
    
    
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__CommUtils__) */
