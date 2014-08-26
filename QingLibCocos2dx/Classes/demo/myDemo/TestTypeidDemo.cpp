//
//  TestTypeidDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 8/20/14.
//
//

#include "TestTypeidDemo.h"
#include "MultiAssetsManager.h"
#include "CommUtils.h"

NS_QING_BEGIN

bool TestTypeidDemo::init()
{
	bool bRet = false;
	do
	{
	    m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestTypeidDemo::TestTypeidDemo()
{
	// TODO: auto generated code
}

TestTypeidDemo::~TestTypeidDemo()
{
	// TODO: auto generated code
}

string callFunc(string format, ... )
{
    va_list args;
    //parmN是省略号"..."前的一个参数名，va_start根据此参数，判断参数列表的起始位置。
    va_start(args, format);
    int len = format.length();
    int key = 1;
    string str1 = "";
    for(int i=0; i<len; i+=2){
        if(format[i] != '%'){   //基数位必须是%
            throw "format 格式错误！";
            return "";
        }
        //这种方式不太对
//        void *pTemp = va_arg(args, void*);
//        CCLOG("类型：%s", typeid(*pTemp).name());
//        continue;
        
        string str = "";
        
        char ch = format[i+1];
        switch (ch) {
            case 'd':{
                str += "int 类型,值是:";
                int value = va_arg(args, int);
                char temp[32];
                sprintf(temp, "%d", value);
                str += temp;
            }
                break;
                
            case 's':{
                str += "string 类型,值是：";
                char *temp = va_arg(args, char *);
                str += temp;
                
            }
                break;
                
            default:
                CCLOG("未实现的格式:%c", ch);
                break;
        }
        char temp[512];
        sprintf(temp, "%s%d%s%s", "第", key, "个参数,", str.c_str());
        str1 += temp;
        str1 += "\n";
//        CCLOG("第%d个参数, %s", key, str.c_str());
        key++;
    }
    
    va_end(args);
    return str1;
}

/**用const char* 代替string */
string callFunc2(const char* format, ... )
{
    va_list args;
    //parmN是省略号"..."前的一个参数名，va_start根据此参数，判断参数列表的起始位置。
    va_start(args, format);
    char *theCursor = (char *)format;
    char ch = 0;
    int key = 1;
    string str1 = "";
    while(*theCursor != '\0'){
        if(*theCursor != '%'){
            throw "format 格式错误！";
            return "";
        }
        ++theCursor;    //跳过百分号
        ch = *theCursor;
        string str = "";
        switch (ch) {
            case 'd':{
                str += "int 类型,值是:";
                int value = va_arg(args, int);
                char temp[32];
                sprintf(temp, "%d", value);
                str += temp;
            }
                break;
                
            case 's':{
                str += "string 类型,值是：";
                char *temp = va_arg(args, char *);
                str += temp;
                
            }
                break;
                
            default:
                CCLOG("未实现的格式:%c", ch);
                break;
        }
        char temp[512];
        sprintf(temp, "%s%d%s%s", "第", key, "个参数,", str.c_str());
        str1 += temp;
        str1 += "\n";
        //        CCLOG("第%d个参数, %s", key, str.c_str());
        key++;
        ++theCursor;
        
    }
    va_end(args);
    return str1;
}


CCLayer* TestTypeidDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
	// TODO: auto generated code
	switch (m_nLayerIndex) {
        case 0:{
            setTitle("typeid 测试");
            
            CCSprite* img = CCSprite::create(s_pPathTexture1);
            layer->addChild(img);
            string str = "";
            char tchar[32] = "aaa";
            str += "char typeid name:";
            str += typeid(tchar).name();
            
            string tstr = "adsfaf";
            str += "\n string typeid name:";
            str += typeid(tstr).name();
            
            int tint = -10000;
            str += "\n int typeid name:";
            str += typeid(tint).name();
            
            int tuint = 10000;
            str += "\n uint typeid name:";
            str += typeid(tuint).name();
            
            float tfloat = -0.5436456;
            str += "\n float typeid name:";
            str += typeid(tfloat).name();
            
            double tdouble = -0.1234567964614313;
            str += "\n double typeid name:";
            str += typeid(tdouble).name();
            
            str += "\n 是否是数字类型:";
            str += tstr;
            str += (typeid(tstr) == typeid(int)) ? "是int!" : "不是int";
            
            str += "\n CCSprite typeid name:";
            str += typeid(CCSprite).name();
            str += "\n CCSprite img typeid name:";
            str += typeid(img).name();
            
            str += "\n 要解指针";
            str += (typeid(*img) == typeid(CCSprite)) ? "CCSprite == sprite img !" : "CCSprite != sprite img ?";
            
            MultiAssetsManager *tmulti = new MultiAssetsManager();
            str += "\n MultiAssetsManager name:";
            str += typeid(*tmulti).name();
            
            createLabel(layer, str);
            
            
        }
            break;
            
        case 1:{
            
            setTitle("可变参数和typeid联合使用? 好像是不能...");
            
            createLabel(layer, callFunc2("%d%s%s%d", 11, "aa", "中文", 99));
        }
            break;
            
        case 2:{
            setTitle("二级指针!");
            int ** ppI;
            int * pI = NULL;
            int num = 100;
            pI = &num;
            ppI = &pI;
            
            CCLOG("一级指针的值 %d", *pI);
            CCLOG("二级指针的值 %d", **ppI);
            CCLOG("二级指针的值 %d", **(int **)ppI); // *(*(int **)ppI)
            
        }
            break;
            
        case 3:{
            setTitle("基本操作");
            int num = -123456789;
            string str = CommUtils::intToString(num);
            CCLOG("int2string : %s", str.c_str());
            char s[32] = {0};
            CommUtils::itoa(num, s);
            CCLOG("itoa : %s", s);
            str = CommUtils::itoa2(num);
            CCLOG("itoa2 : %s", str.c_str());
            
            string tempS = "987654321";
            int tempI = CommUtils::stringToInt(tempS);
            CCLOG("stringToInt : %d", tempI);
            
            float tempF = -12345.12f;
            str = CommUtils::numberToString(tempF);
            CCLOG("numberToString float : %s", str.c_str());
            
            str = CommUtils::numberToString(-12345);
            CCLOG("numberToString int : %s", str.c_str());
            
            float tempF2 = CommUtils::stringToNumber<float>("12345.12f");
            CCLOG("stringToNumber float : %f", tempF2);
            
            tempI = CommUtils::stringToNumber<int>("-12345");
            CCLOG("stringToNumber int : %d", tempI);
            
        }
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

NS_QING_END