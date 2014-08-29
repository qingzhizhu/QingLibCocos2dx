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

#pragma mark- 时间

string CommUtils::getTime()
{
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return tmp;
}

string CommUtils::getTime(int time)
{
    struct cc_timeval now;
    now.tv_sec = time;
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&now.tv_sec));
    return tmp;
}

string CommUtils::getTimeDate(int time)
{
    struct cc_timeval now;
    now.tv_sec = time;
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&now.tv_sec));
    return tmp;
}

string CommUtils::getTimeAgo(int nTime)
{
    time_t t = time(0);
    t -= nTime;
    if(t <= 0){
        return "now";
    }
    int d = t / 86400;
    int h = (t / 3600) % 24;
    int m = (t / 60) % 60;
    int s = t % 60;
    
    string str = "";
    if(d > 0){
        str += numberToString(d);
        str + "D";
    }
    
    if(h > 0){
        str += numberToString(h);
        str += "H";
    }
    
    if(m > 0){
        str += numberToString(m);
        str += "M";
    }
    
    if(s > 0){
        str += numberToString(s);
        str += "S";
    }
    
    return str;
}

string CommUtils::getClockTime(int time, int limitMaxSpan, bool shortFlag)
{
    struct cc_timeval now;
    now.tv_sec = time;
    struct tm *tm = localtime(&now.tv_sec);
    string str = "";
    //最多显示两个单位， 例如：“1天12小时”， “12小时30分”，“30分40秒”
    int curSpan = 0;
    if(tm->tm_mday > 0 && curSpan < limitMaxSpan){
        str += numberToString(tm->tm_mday);
        str += "D";
        curSpan++;
    }
    
    if(tm->tm_hour > 0 && curSpan < limitMaxSpan){
        str += numberToString(tm->tm_hour);
        str += "H";
        curSpan++;
    }
    
    if(tm->tm_min > 0 && curSpan < limitMaxSpan){
        str += numberToString(tm->tm_min);
        str += shortFlag ? "M" : "Min";
        curSpan++;
    }
    
    if(tm->tm_sec > 0 && curSpan < limitMaxSpan){
        str += numberToString(tm->tm_sec);
        str += shortFlag ? "S" : "Secs";
        curSpan++;
    }
    
    return str;
}

int CommUtils::getTimeStamp()
{
    //2种方式都ok
//    time_t now;
//    time(&now);
//    return now;
    return secondNow();
}

int CommUtils::secondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return now.tv_sec;

}

int64_t CommUtils::millSecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    int64_t millSecond = (int64_t)now.tv_sec * (int64_t)1000 + now.tv_usec / 1000;
    return millSecond;
}

int64_t CommUtils::microSecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);    
    int64_t microSecond = (int64_t)now.tv_sec * (int64_t)1000000 + now.tv_usec;
    return microSecond;
}




#pragma mark- basic method
/*
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
*/











