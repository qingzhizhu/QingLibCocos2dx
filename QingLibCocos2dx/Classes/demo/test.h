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
#include "TestLocalLuaDemo.h"
#include "TestLayerDemo.h"
#include "TestSpriteDemo.h"
#include "TestClippingNodeDemo.h"
#include "StorageUtilsTest.h"
#include "TestXMLDemo.h"
#include "TestFileUtils.h"
#include "TestMultiAssetsManager.h"
#include "TestNetworkDemo.h"
#include "TestDeviceInfoDemo.h"
#include "TestThreadDemo.h"
#include "TestTypeidDemo.h"

enum{
    TESTS_MYDEMO = 0,
    TESTS_FONT,
    TESTS_LUA,
    TESTS_MYMANAGER,
    TESTS_MULTI_MANAGER,
    TESTS_LAYER,
    TESTS_SPRITE,
    TESTS_CLIPPINGNODE,
    TESTS_UTILS_STORAGE,
    TESTS_IO_FILE,
    TESTS_IO_XML,
    TESTS_NETWORK,
    TESTS_DEVICE_INFO,
    TESTS_PTHREAD,
    TESTS_TYPEID_TEST,
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
    "Lua Demo",
    "Lua & AssetsManager",
    "Multi AssetsManager!",
    "Layer Tests",
    "Sprite Tests",
    "CCClippingNode Tests!",
    "Storage Utils Test.",
    "IO - File Test!",
    "IO - XML Test!",
    "NetWork Demo!",
    "Device Info!",
    "pthread Demo!",
    "typeid compare class type!",
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
