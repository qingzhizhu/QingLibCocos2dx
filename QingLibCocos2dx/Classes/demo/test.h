//
//  test.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 13-12-26.
//
//
/// 这个文件主要是测试类的引用

#ifndef QingLibCocos2dx_test_h
#define QingLibCocos2dx_test_h

enum{
    TEST_MYDEMO = 0,
    
    // last one
	TESTS_COUNT,
};


const std::string g_aTestNames[TESTS_COUNT] = {
    "My Demo!"
    
};


//resource

static const char s_pPathClose[]          = "CloseNormal.png";

#endif
