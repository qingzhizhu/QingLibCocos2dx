//
//  TestMyDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//

#include "TestMyDemo.h"
#include "VisibleRect.h"

USING_NS_QING;

bool TestMyDemo::init()
{
	bool bRet = false;
	do
	{
		// TODO: auto generated code
//        CCLayer.init()实现体，开启滚动用 m_bTouchEnabled = true;
//        CCDirector * pDirector;
//        CC_BREAK_IF(!(pDirector = CCDirector::sharedDirector()));
//        this->setContentSize(pDirector->getWinSize());
        m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestMyDemo::TestMyDemo()
: m_pLbl(NULL)
, m_nLblWid(0)
, m_nLblHei(0)
, m_nMoved(0)
, m_nHei(90)
{
    m_nLblWid = VisibleRect::getVisibleRect().size.width - 100;
    
}

TestMyDemo::~TestMyDemo()
{
    
}

void TestMyDemo::onEnter()
{
    TestBaseLayer::onEnter();
    
    CCLayer* layer = CCLayerColor::create(ccc4(0xFF, 0x99, 0xCC, 0xEE));
    addChild(layer, -1);
    CCLabelTTF* lbl = CCLabelTTF::create("", FONT_NAME, FONT_SIZE);
    lbl->setDimensions(CCSizeMake(m_nLblWid, 0));
    lbl->setPosition(VisibleRect::center());
    addChild(lbl, 2);
    m_pLbl = lbl;
    
    m_pLbl->setVisible(false);    //防止一上来就显示很多文字
    
    m_pLbl->setString("\n桃花庵歌 \n作者：唐伯虎 \n \n桃花坞里桃花庵，桃花庵里桃花仙； \n桃花仙人种桃树，又摘桃花换酒钱。 \n酒醒只在花前坐，酒醉还来花下眠； \n半醉半醒日复日，花开花落年复年。 \n但愿老死花酒间，不愿鞠躬车马前； \n车尘马后富者趣，酒盏花枝贫者缘。 \n若将富贵比贫者，一在平地一在天； \n若将贫贱比车马，他得驱使我得闲。 \n别人笑我忒疯癫，我笑他人看不穿； \n不见五陵豪杰慕，无花无酒锄作田！ \n");
    m_nLblHei = m_pLbl->getContentSize().height;
    m_nMoved = 0;
    //大于90才滚动
    m_nHei = 120;
    if(m_nLblHei > m_nHei){
        addScheduler(true);
    }
}

void TestMyDemo::addScheduler(bool isAdd)
{
    if(isAdd){
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(TestMyDemo::doEnterFrame), this, 0.1f, false);
    }else{
        //消除定时器
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(TestMyDemo::doEnterFrame), this);
    }
}

void TestMyDemo::doEnterFrame(float time)
{
    if(m_nMoved == 0){
        m_pLbl->setVisible(true);
    }
    m_nMoved ++;
    m_pLbl->setTextureRect(CCRectMake(0, m_nMoved, m_nLblWid, m_nHei));
    if(m_nMoved > m_nLblHei){
        m_nMoved = 0;
    }
}

