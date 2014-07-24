//
//  LuaEngineUtils.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-3-27.
//
//

#include "LuaEngineUtils.h"

#include "CCLuaEngine.h"

USING_NS_QING;


LuaEngineUtils::LuaEngineUtils()
{
    
}

LuaEngineUtils::~LuaEngineUtils()
{
    
}

bool LuaEngineUtils::sm_bInited = false;

const char * LuaEngineUtils::fullPathForFilename(const char *fileName)
{
    return CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName).c_str();
}


lua_State* LuaEngineUtils::getLuaState()
{
    return CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
}


bool LuaEngineUtils::isOpenLua(const char *luaFileName)
{
    int result = luaL_dofile(getLuaState(), fullPathForFilename(luaFileName));
    if(result != 0){
        CCLOG("Open lua error = %d ", result);
    }
    return result == 0;
}


int LuaEngineUtils::executeLua(const char *luaFileName)
{
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    if(!sm_bInited){
        sm_bInited = true;
        // register lua engine
        CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    }
    return pEngine->executeScriptFile(fullPathForFilename(luaFileName));
}


lua_State * LuaEngineUtils::getLuaStateByFunName(const char *luaFileName, const char *funName)
{
    lua_State* ls = getLuaState();
    if(isOpenLua(luaFileName)){
        lua_getglobal(ls, funName);
        return ls;
    }
    CCLOG("Open Lua Error  getLuaStateByFunName: file = %s, fun = %s", luaFileName, funName);
    return NULL;
}


const char* LuaEngineUtils::getLuaVarString(const char *luaFileName, const char *varName)
{
    if(isOpenLua(luaFileName)){
        lua_State* ls = getLuaState();
        lua_settop(ls, 0);
        lua_getglobal(ls, varName);
        int statesCode = lua_isstring(ls, 1);
        if(statesCode != 1){
            CCLOG("Read Var String error = %d", statesCode);
            return NULL;
        }
        const char* str = lua_tostring(ls, 1);
        lua_pop(ls, 1);
        return str;
        
    }
    return NULL;
}

const char* LuaEngineUtils::getLuaVarTable(const char *luaFileName, const char *varName)
{
    if(isOpenLua(luaFileName)){
        lua_State* ls = getLuaState();
        lua_getglobal(ls, varName);
        int it = lua_gettop(ls);
        lua_pushnil(ls);
        string result = "";
        while (lua_next(ls, it)) {
            string key = lua_tostring(ls, -2);
            string value = lua_tostring(ls, -1);
            result += key + ":" + value + "\t";
            lua_pop(ls, 1);
        }
        lua_pop(ls, 1);
        return result.c_str();
    }
    return NULL;
}

const char* LuaEngineUtils::getLuaVarTableProp(const char *luaFileName, const char *varName, const char *key)
{
    if(isOpenLua(luaFileName)){
        lua_State* ls = getLuaState();
        lua_getglobal(ls, varName);
        int statusCode = lua_istable(ls, -1);
        if(statusCode != 1){
            CCLOG("Read Var Table error = %d", statusCode);
            return NULL;
        }
        lua_pushstring(ls, key);
        lua_gettable(ls, -2);
        const char* str = lua_tostring(ls, -1);
        lua_pop(ls, -1);
        return str;
    }
    return NULL;
}


const char* LuaEngineUtils::callLuaFunc(const char *luaFileName, const char *funcName, ... )
{
    if(isOpenLua(luaFileName)){
        lua_State* ls = getLuaState();
        lua_getglobal(ls, funcName);
        
        //TODO: 需要解析类型 [type,value...]
        
        lua_pushstring(ls, "?");
        lua_pushnumber(ls, 1);
        lua_pushboolean(ls, false);
        
        int nargs = 1;  //可变参数的个数
        lua_call(ls, nargs, 1);
        return lua_tostring(ls, -1);
    }
    return NULL;
}

void LuaEngineUtils::callCppFunc()
{
//    lua_State*  ls = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
//    
//    /*
//     Lua调用的C++的函数必须是静态的
//     */
//    lua_register(ls, "cppFunction", cppFunction);
//    
//    int isOpen = luaL_dofile(ls, getFileFullPath(luaFileName));
//    if(isOpen!=0){
//        CCLOG("Open Lua Error: %i", isOpen);
//        return;
//    }
}


//int HclcData::cppFunction(lua_State* ls){
//    int luaNum = (int)lua_tonumber(ls, 1);
//    int luaStr = (int)lua_tostring(ls, 2);
//    CCLOG("Lua调用cpp函数时传来的两个参数： %i  %s",luaNum,luaStr);
//    
//    /*
//     返给Lua的值
//     */
//    lua_pushnumber(ls, 321);
//    lua_pushstring(ls, "Himi");
//    
//    /*
//     返给Lua值个数
//     */
//    return 2;
//}


