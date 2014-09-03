//
//  StringUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-11.
//
//

#include "StringUtils.h"
#include <algorithm>

USING_NS_QING;


StringUtils::StringUtils()
{
    
}

StringUtils::~StringUtils()
{
    
}

void StringUtils::toLower(string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void StringUtils::toUpper(string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void StringUtils::trim(string &str, bool left, bool right)
{
    static const string delims = " \a\b\f\n\r\t\v";
    if(left){
        str.erase(0, str.find_first_not_of(delims));
    }
    if(right){
        str.erase(str.find_first_not_of(delims) + 1);
    }
}

string& StringUtils::replaceAll(string &src, const string &oldStr, const string &newStr)
{
    for(string::size_type pos(0); pos != string::npos; pos+=newStr.length()){
        if((pos=src.find(oldStr,pos)) != string::npos){
            src.replace(pos, oldStr.length(), newStr);
        }else{
            break;
        }
    }
    return src;
}

string StringUtils::format(const char *format, ...)
{
    const size_t len = 10240;
    static char buf[len] = {0};
    memset(buf, 0, len);
    va_list args;
    va_start(args, format);
    vsnprintf(buf, len, format, args);
    va_end(args);
    return buf;
}

bool StringUtils::equal(const char *s1, const char *s2)
{
    if(s1 == NULL && s2 == NULL){
        return true;
    }
    if(s1 == NULL || s2 == NULL){
        return false;
    }
    return strcmp(s1, s1) == 0;
}

void StringUtils::split(const char *src, const char *token, vector<string> &vect)
{
    if(src == NULL || token == NULL) return;
    int len = strlen(src);
    if(len == 0) return;
    char *pBuf = (char *)malloc(len + 1);
    strcpy(pBuf, src);
    char *str = strtok(pBuf, token);
    while (str != NULL) {
        vect.push_back(str);
        str = strtok(NULL, token);
    }
    free(pBuf);
}


void StringUtils::splitStr(string src, const char *token, vector<string> &vect)
{
    if(src.length() == 0){
        return;
    }
    size_t begin = 0;
    size_t end = 0;
    while (end != string::npos) {
        end = src.find_first_of(token, begin);
        if(end == string::npos){
            vect.push_back(src.substr(begin, src.length() - begin));
        }else{
            vect.push_back(src.substr(begin, end - begin));
        }
        begin = end + strlen(token);
    }
}


//key1=v1;key2=v2;


string StringUtils::join(vector<string> &arr, const char *separator)
{
    string str = "";
    for (vector<string>::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
        str += *iter + *separator;
    }
    return str;
}




int StringUtils::calcHashKey(string str)
{
    if (str.length() == 0)
    {
        return 0;
    }
    uint uHashVal = 2166136261U;
    uint uLast = (uint)str.length();
    for(uint uFirst = 0; uFirst < uLast; ++uFirst)
    {
        //2^24
        uHashVal = 16777619U * uHashVal ^ (uint)str[uFirst];
    }
    return abs((int)(uHashVal));
}












