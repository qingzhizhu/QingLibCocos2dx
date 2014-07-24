//
//  LuaEngineUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-3-27.
//
//

#ifndef __QingLibCocos2dx__LuaEngineUtils__
#define __QingLibCocos2dx__LuaEngineUtils__

#include "Common.h"


extern "C" {
    //#include "lua.h"
    //#include "lualib.h"
#include "lauxlib.h"
};

NS_QING_BEGIN


class LuaEngineUtils
{
public:
    LuaEngineUtils();
	~LuaEngineUtils();
    
    
    /**返回文件的完整路径*/
    static const char * fullPathForFilename(const char* luaFileName);
    
    /**获取lua state*/
    static lua_State* getLuaState();
    
    /**是否能打开lua文件*/
    static bool isOpenLua(const char* luaFileName);
    
#pragma mark- C call lua.
    
    /**
     * 执行lua文件
     *
     */
    static int executeLua(const char* luaFileName);
    
    
    
    /**
     * 根据 方法名称返回lua_state 指针
     */
    static lua_State * getLuaStateByFunName(const char* luaFileName, const char* funName);
    
    
    /**
     * 获取lua全局的string
     *
     */
    static const char* getLuaVarString(const char* luaFileName, const char* varName);
    
    
    /**
     * 调用lua全局table
     * @return TODO: 是否改为Map?
     */
    static const char* getLuaVarTable(const char* luaFileName, const char* varName);
    
    /**
     * 获取table的某个属性
     * @return
     */
    static const char* getLuaVarTableProp(const char* luaFileName, const char* varName, const char* key);
    
    
    /**
     * 调用lua 的函数
     * @param args 可变参数 TODO:
     */
    static const char* callLuaFunc(const char* luaFileName, const char* funcName, ... );
    
    
    
    
#pragma mark-
    
    
#pragma mark- lua call C.
    
    static void callCppFunc();
    
#pragma mark-
    
    
protected:
    
    static bool sm_bInited;
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__LuaEngineUtils__) */
