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
    
    static void toLower(string &str);
    static void toUpper(string &str);
    
    /**删除两边的空格*/
    static void trim(string &str, bool left, bool right);
    
    /**替换*/
    static string& replaceAll(string& src, const string& oldStr, const string& newStr);
    
    /**格式化输出*/
    static string format(const char *format, ...);
    
    /**是否相同*/
    static bool equal(const char *s1, const char *s2);
    
    
    /** 
     * 把字符串转为字符数组 
     * @param src 
     * @param token 可以为复数，如 " ,.-"
     */
    static void split(const char* src, const char* token, vector<string>& vect);
    /**速度慢，耗内存*/
    static void splitStr(string src, const char* token, vector<string> &vect);
    
    /**连接字符串*/
    static string join(vector<string> &arr, const char* separator);
    
//    /** 字符串切分保存到字典 */
//    static void strToDic(string str, const char* token1, const char* token2, CCDictionary* dic);
//    
//    /** 字符串切分保存到数组 */
//    static void strToCCArray(string str, const char* token, CCArray* arr);
    
    
    
    static int calcHashKey(string str);
    
private:
    
    StringUtils();
	~StringUtils();
    
    
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__StringUtils__) */
