//
//  TestXMLDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-3.
//
//

#include "TestXMLDemo.h"

#include "support/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

USING_NS_QING;

bool TestXMLDemo::init()
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

TestXMLDemo::TestXMLDemo()
{
	// TODO: auto generated code
}

TestXMLDemo::~TestXMLDemo()
{
	// TODO: auto generated code
}

string getXMLPath()
{
    return CCFileUtils::sharedFileUtils()->getWritablePath() + "IOTest.xml";
}

CCLayer* TestXMLDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();

	switch (m_nLayerIndex) {
        case 0:{
            setTitle("XML 的创建, 使用tinyxml2 速度慢！");
            XMLDocument* doc = new XMLDocument();
            if(doc == NULL){
                CCLOG("XMLDocuemnt 创建失败");
                return layer;
            }
            //xml 声明
            XMLDeclaration* decl = doc->NewDeclaration();
            if(decl == NULL){
                CCLOG("XMLDeclaration 声明 失败");
                return layer;
            }
            doc->LinkEndChild(decl);
            XMLElement* rootEle = doc->NewElement("Kevin");
            doc->LinkEndChild(rootEle);
            rootEle->SetAttribute("version", "1.0");
            
            XMLElement* infoEle = doc->NewElement("info");
            rootEle->LinkEndChild(infoEle);
            //设置属性
            infoEle->SetAttribute("name", "Kevin G.");
            infoEle->SetAttribute("email", "gengkun123@gmail.com");
            
            XMLElement* blog = doc->NewElement("blog");
            infoEle->LinkEndChild(blog);
            //节点文本
            XMLText* blogTxt = doc->NewText("http://qingzhizhu.github.com/");
            blogTxt->SetCData(true);
            blog->LinkEndChild(blogTxt);
            
            //节点array
            XMLElement *arrayElemet = doc->NewElement("array");
            //注释
            XMLComment* commnet = doc->NewComment("array 的注释...");
            arrayElemet->LinkEndChild(commnet);
            
            for (int i = 0; i<3; i++) {
                XMLElement *strEle = doc->NewElement("string");
                strEle->LinkEndChild(doc->NewText("icon"));
                arrayElemet->LinkEndChild(strEle);
            }
            infoEle->LinkEndChild(arrayElemet);
            
            //Unknown.
            rootEle->LinkEndChild(doc->NewUnknown("Un known..."));
            
            XMLError err = doc->SaveFile(getXMLPath().c_str());
            
            
            CCLabelTTF* lbl = CCLabelTTF::create("", FONT_NAME, FONT_SIZE);
            lbl->setPosition(VisibleRect::center());
            layer->addChild(lbl);
            string str = "";
            if(err == XML_SUCCESS){
                CCLOG("xml 写入成功！");
                str = "xml 写入成功！\n" + getXMLPath();
            }else{
                CCLOG("xml 写入失败 code = %d", err);
                str = "xml 写入失败 code = ";
            }
            lbl->setString(str.c_str());
//            XMLPrinter* printer = new XMLPrinter();
            doc->Print();
            
            delete doc;
            doc = NULL;
            
        }
            break;
            
        case 1:{
            setTitle("XML 的读取, 使用tinyxml2 速度慢！");
            
            string str = "";
            
            XMLDocument* doc = new XMLDocument();
            XMLError error = doc->LoadFile(getXMLPath().c_str());
            if(error == XML_SUCCESS){
                XMLElement* rootEle = doc->RootElement();
                str = "root name:";
                str += rootEle->Name();
                CCLog("%s",rootEle->GetText());
                
                const XMLAttribute* attr = rootEle->FirstAttribute();
                str += "\n";
                str += "属性名称";  str += attr->Name();
                str += "值：";    str += attr->Value();
                str += "\n";
                float ver = 0.0f;
                rootEle->QueryFloatAttribute("version", &ver);
                str += "version 属性值";
                CCLOG("version: %f", ver);
                
                rootEle->SetAttribute("version", "1.01");
                str += "\n";
                XMLElement* infoEle = rootEle->FirstChildElement();
                str += "info name:";
                str += infoEle->Name();
                
                XMLElement* unKnownEle = infoEle->NextSiblingElement();
                if(unKnownEle){
                    str += "\n";
                    str += "unKnown"; str += unKnownEle->GetText();
                }
                
                XMLElement* blogEle = infoEle->FirstChildElement();
                
                str += "\n";
                str += "blog name:";    str += blogEle->Name();
                str += "\tvalue"; str += blogEle->Value();
                str += "\ttext:"; str += blogEle->GetText();
                
                XMLElement* nullEle = blogEle->FirstChildElement();
                if(!nullEle){
                    str += "\n";
                    str += "info 下没有节点了";
                }
                
                doc->SaveFile(getXMLPath().c_str());
                
            }else{
                CCLOG("xml 打开失败 code = %d", error);
                str = "打开失败";
            }
            CCLabelTTF* lbl = CCLabelTTF::create(str.c_str(), FONT_NAME, FONT_SIZE);
            lbl->setPosition(VisibleRect::center());
            layer->addChild(lbl);
        }
            break;
            
        case 2:
            setTitle("RapidXML 解析效率是TinyXML的30到60倍 \n资料: http://blog.csdn.net/jackystudio/article/details/17409381 ");
            
            
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

