//
//  TestFileUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-5.
//
//

#include "TestFileUtils.h"
#include "FileUtils.h"

USING_NS_QING;

bool TestFileUtils::init()
{
	bool bRet = false;
	do
	{
		// TODO: auto generated code
        m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestFileUtils::TestFileUtils()
{
    
}

TestFileUtils::~TestFileUtils()
{
    
}


void TestFileUtils::onEnter()
{
	TestBaseLayer::onEnter();
	
    setTitle("读写文件");
    
    string str = "\n桃花庵歌 \n作者：唐伯虎 \n \n桃花坞里桃花庵，桃花庵里桃花仙； \n桃花仙人种桃树，又摘桃花换酒钱。 \n酒醒只在花前坐，酒醉还来花下眠； \n半醉半醒日复日，花开花落年复年。 \n但愿老死花酒间，不愿鞠躬车马前； \n车尘马后富者趣，酒盏花枝贫者缘。 \n若将富贵比贫者，一在平地一在天； \n若将贫贱比车马，他得驱使我得闲。 \n别人笑我忒疯癫，我笑他人看不穿； \n不见五陵豪杰慕，无花无酒锄作田！ \n";
    string path = "ty.txt";
    
    
    CCLabelTTF* lbl = CCLabelTTF::create("", FONT_NAME, FONT_SIZE);
    lbl->setPosition(VisibleRect::center());
    addChild(lbl);
    bool b = FileUtils::save(path, str);
    str = b ? "写入成功" : "写入失败";
    
    string data = "";
    path = "ZangHuaYin.txt";
    FileUtils::loadFile(path, data, FILE_PATH_TYPE_FULLPATH);
    str += "\n";
    str += data;
    
    lbl->setString(str.c_str());
    
    
    
}

void TestFileUtils::onExit()
{
	TestBaseLayer::onExit();
    
}

