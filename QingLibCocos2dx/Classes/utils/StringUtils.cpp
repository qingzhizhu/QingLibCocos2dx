//
//  StringUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-11.
//
//

#include "StringUtils.h"


USING_NS_QING;


StringUtils::StringUtils()
{
    
}

StringUtils::~StringUtils()
{
    
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

















