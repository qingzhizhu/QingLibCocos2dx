//
//  LabelUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-2-11.
//
//
/// 文本相关的操作

#ifndef __QingLibCocos2dx__LabelUtils__
#define __QingLibCocos2dx__LabelUtils__

#include "Common.h"

NS_QING_BEGIN

//描边RenderTexture 的tag
#define TAG_STROKE 123

class LabelUtils
{
public:
    LabelUtils();
	~LabelUtils();
    
    /**
     * 描边
     * @param label 
     * @param size 描边尺寸,默认2
     * @param color 描边颜色，默认黑色
     */
    static void createStroke(CCLabelTTF *label, float size = 2, ccColor3B color = ccBLACK);
    
    
    /**
     * 对文本进行自适应
     * @param tfStr 文本
     * @param subStr 是否截取字符串显示 如 文字...,false 是缩小字体显示
     */
    static void fitLabelText(CCLabelTTF* label, string tfStr, bool subStr=false);
    
    
    
    
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__LabelUtils__) */
