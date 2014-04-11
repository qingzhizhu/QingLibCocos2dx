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

#include "TestMyDemo.h"
#include "TestFontDemo.h"
#include "MyAssetsManagerDemo.h"
#include "TestLuaDemo.h"
#include "TestLayerDemo.h"
#include "TestSpriteDemo.h"
#include "TestClippingNodeDemo.h"

enum{
    TESTS_MYDEMO = 0,
    TESTS_FONT,
    TESTS_MYMANAGER,
    TESTS_LUA,
    TESTS_LAYER,
    TESTS_SPRITE,
    TESTS_CLIPPINGNODE,
    TESTS_MYDEMO11,
    TESTS_MYDEMO12,
    TESTS_MYDEMO13,
    TESTS_MYDEMO14,
    TESTS_MYDEMO15,
    TESTS_MYDEMO16,
    TESTS_MYDEMO21,
    TESTS_MYDEMO22,
    TESTS_MYDEMO23,
    TESTS_MYDEMO24,
    TESTS_MYDEMO25,
    TESTS_MYDEMO26,
    TESTS_MYDEMO211,
    TESTS_MYDEMO212,
    TESTS_MYDEMO213,
    TESTS_MYDEMO214,
    TESTS_MYDEMO215,
    TESTS_MYDEMO216,
    // last one
	TESTS_COUNT,
};


const std::string g_aTestNames[TESTS_COUNT] = {
    "My Demo!",
    "Font Test",
    "MyAssetsManager",
    "Lua & AssetsManager",
    "Layer Tests",
    "Sprite Tests",
    "CCClippingNode Tests!",
    "My Demo====11!",
    "My Demo====12!",
    "My Demo====13!",
    "My Demo====14!",
    "My Demo====15!",
    "My Demo====16!",
    "My Demo====21!",
    "My Demo====22!",
    "My Demo====23!",
    "My Demo====24!",
    "My Demo====25!",
    "My Demo====26!",
    "My Demo====211!",
    "My Demo====212!",
    "My Demo====213!",
    "My Demo====214!",
    "My Demo====215!",
    "My Demo====216!",
};


#endif
