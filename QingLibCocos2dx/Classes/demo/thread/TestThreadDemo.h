//
//  TestThreadDemo.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 8/5/14.
//
//
/// 底部带回退，重置，前进按钮

#ifndef __QingLibCocos2dx__TestThreadDemo__
#define __QingLibCocos2dx__TestThreadDemo__

#include "Common.h"
#include "TestBaseDemo.h"

NS_QING_BEGIN


class TestThreadDemo : public TestBaseDemo
{
public:
	virtual bool init();
	CREATE_FUNC(TestThreadDemo);
	TestThreadDemo();
	virtual ~TestThreadDemo();

	/**子类复写，根据当前下标显示相应的子demo*/
    virtual CCLayer* getLayerByIndex();
    /**子类复写，返回测试layer的数量*/
    virtual int getLayerLen() { return 1; }
    
    
    
protected:  //layer 1
    
    pthread_t m_threadA;
    pthread_t m_threadB;
    
    static void* threadA(void* p);
    static void* threadB(void* p);
    
    int m_nTickets;
    
    pthread_mutex_t m_mutex;
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__TestThreadDemo__) */
