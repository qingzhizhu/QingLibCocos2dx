//
//  DisplayObjectUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-4-8.
//
//
/// 显示对象的工具类

#ifndef __QingLibCocos2dx__DisplayObjectUtils__
#define __QingLibCocos2dx__DisplayObjectUtils__

#include "Common.h"

NS_QING_BEGIN


class DisplayObjectUtils
{
public:
    DisplayObjectUtils();
	~DisplayObjectUtils();
    
    
#pragma mark- 图片相关
    
    /**
     * 平铺图片
     * @param img 文理的宽高必是2的n次方，如64*32...
     * @param size 平铺的尺寸
     */
    static void repeatImg(CCSprite* img, const CCSize& size);
    
    
    /**
     * 设置图片的遮罩, CCRenderTexture 性能较低，得到的文理Y轴是反的
     */
    static CCSprite* maskImg(CCSprite* src, const CCSize& size);
    static CCSprite* maskImg(CCSprite* src, CCBlendProtocol* mask);
    
#pragma mark-
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__DisplayObjectUtils__) */
