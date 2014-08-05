//
//  TestThreadDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 8/5/14.
//
//

#include "TestThreadDemo.h"

NS_QING_BEGIN

bool TestThreadDemo::init()
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

TestThreadDemo::TestThreadDemo()
: m_nTickets(100)
, m_threadA(NULL)       //???
, m_threadB(NULL)
{
    m_nTickets = 100;
    pthread_mutex_init(&m_mutex, NULL);
}

TestThreadDemo::~TestThreadDemo()
{
    pthread_mutex_destroy(&m_mutex);
}

void* TestThreadDemo::threadA(void *p)
{
    TestThreadDemo *self = (TestThreadDemo*)p;
    while(true){
        pthread_mutex_lock(&self->m_mutex);
        if(self->m_nTickets > 0){
            CCLOG("A sell ticket:%d.", self->m_nTickets--);
        }
        pthread_mutex_unlock(&self->m_mutex);
        if(self->m_nTickets <= 0) break;
        sleep(1);
    }
    
    return NULL;
}

void* TestThreadDemo::threadB(void *p)
{
    TestThreadDemo *self = (TestThreadDemo*)p;
    while(true){
        pthread_mutex_lock(&self->m_mutex);
        if(self->m_nTickets > 0){
            CCLOG("B sell ticket:%d.", self->m_nTickets--);
        }
        pthread_mutex_unlock(&self->m_mutex);
        if(self->m_nTickets <= 0) break;
        sleep(1);
    }
    return NULL;
}


CCLayer* TestThreadDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();
	// TODO: auto generated code
	switch (m_nLayerIndex) {
        case 0:
            setTitle("pthread 售票");
            
            pthread_create(&m_threadA, NULL, threadA, this);
            pthread_create(&m_threadB, NULL, threadB, this);
            
            
            
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

NS_QING_END