//
//  CommUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-11.
//
//

#include "CommUtils.h"


#include <regex.h>




USING_NS_QING;


CommUtils::CommUtils()
{
    
}

CommUtils::~CommUtils()
{
    
}

uint CommUtils::getColor(unsigned char r, unsigned char g, unsigned char b)
{
    return r << 16 | g << 8 | b;
}


void CommUtils::getRGB(uint color, int *ret)
{
    ret[0] = (color >> 16) & 0xFF;  //red
    ret[1] = (color >> 8) & 0xFF;   //green
    ret[2] = color & 0xFF;          //blue
}


#pragma mark- 正则

/**是否是email格式*/
bool CommUtils::isEmail(string& str)
{
    bool result = false;
    const char *eset = "[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
    regmatch_t subs[10];
    regex_t reg;
    regcomp(&reg, eset, REG_EXTENDED);
    int err = regexec(&reg, str.c_str(), (size_t)10, subs, 0);
    if(err == REG_NOMATCH){
        CCLOG("邮箱格式不匹配");
    }else if(err == 0){
        result = true;
    }
    regfree(&reg);
    return result;
}

/**是否是密码格式*/
bool CommUtils::isPassword(string& str)
{
    bool result = false;
    const char *eset = "^[a-zA-Z0-9_]{8,16}$";
    regmatch_t subs[10];
    regex_t reg;
    regcomp(&reg, eset, REG_EXTENDED);
    int err = regexec(&reg, str.c_str(), (size_t)10, subs, 0);
    if(err == REG_NOMATCH){
        CCLOG("密码格式不匹配");
    }else if(err == 0){
        result = true;
    }
    regfree(&reg);
    return result;
}



#pragma mark- basic method

int CommUtils::strLenMy(char s[])
{
    int i =0;
    while(s[i] != '\0'){
        i++;
    }
    return i;
}


void CommUtils::reverseStr(char s[])
{
    char c;
    for(int i=0,j=strLenMy(s)-1; i<j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


string CommUtils::intToString(int value)
{
//    char buffer[32];
//    sprintf(buffer, "%d", value);
//    return buffer;
    return string(itoa2(value));
}


void CommUtils::itoa(int value, char s[])
{
    int i = 0, sign = 0;
    if((sign = value) < 0){
        value = -value;
    }
    do{
        s[i++] = value % 10 + '0';
    }while ( (value/=10) > 0);
    if(sign < 0){
        s[i++] = '-';
    }
    s[i] = '\0';
    reverseStr(s);
}

static map<int, string> s_dicStrNum;
const char* CommUtils::itoa2(int value)
{
    auto iter = s_dicStrNum.find(value);
    if(iter != s_dicStrNum.end()){
        return iter->second.c_str();
    }
    static char strBuffer[24] = {0};
    strBuffer[sprintf(strBuffer, "%d", value)] = '\0';
    s_dicStrNum.insert(make_pair(value, strBuffer));
    iter = s_dicStrNum.find(value);
    if(iter != s_dicStrNum.end()){
        return iter->second.c_str();
    }
    return NULL;
}

int CommUtils::stringToInt(string value)
{
    return atoi(value.c_str());
}


int CommUtils::atoiMy(char *s)
{
    int n = 0;
    for(int i=0; s[i]>= '0' && s[i] <= '9'; ++i){
        n = n * 10 + (s[i] - '0');
    }
    return n;
}


string CommUtils::floatToString(float value)
{
    stringstream os;
    os << value;
    return os.str();
}











