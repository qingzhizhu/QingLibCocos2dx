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
    
#pragma mark- 颜色
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
    
    
#pragma mark- 时间
    /**获取时间*/
    static string getTime();
    /**获取时间 time*/
    static string getTime(int time);
    /**日期*/
    static string getTimeDate(int time);
    /**时间差*/
    static string getTimeAgo(int time);
    /**
     * 时钟时间
     * limitMaxSpan 显示精确度
     * shortFlag true: xx天xx时xx分 ; false: xx天xx小时xx分钟
     */
    static string getClockTime(int time, int limitMaxSpan = 3, bool shortFlag = true);
    
    /**时间戳*/
    static int getTimeStamp();
    /**获取当前时间 秒*/
    static int secondNow();
    /**获取当前时间 毫秒*/
    static int64_t millSecondNow();
    /**获取当前时间 微秒*/
    static int64_t microSecondNow();
    
    
    
#pragma mark- basic method
    /*
    //c++ 11 都支持下面的函数
    static int strLenMy(char s[]);
    static void reverseStr(char s[]);
    
    static string intToString(int value);
    static void itoa(int value, char s[]);
    static const char* itoa2(int value);
    static int stringToInt(string value);
    static int atoiMy(char s[]);
    
    static string floatToString(float value);
    static float stringToFloat(string value);
    */
    
    /**
     * 数字转字符串
     * Usage: NumberToString ( Number );
     */
    template <typename T> static inline string numberToString(T number)
    {
        ostringstream ss;
        ss << number;
        return ss.str();
    }
    
    /**
     * 字符串转数字
     * Usage: StringToNumber<Type> ( String );
     */
    template <typename T> static inline T stringToNumber(const string &str)
    {
        istringstream ss(str);
        T result;
        return ss >> result ? result : 0;
    }
    
    
private:
    CommUtils();
	~CommUtils();
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__CommUtils__) */
