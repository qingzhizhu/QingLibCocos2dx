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



#pragma mark-
