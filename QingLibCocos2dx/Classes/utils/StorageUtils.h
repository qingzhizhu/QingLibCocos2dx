//
//  StorageUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-2.
//
//
/// 存储客户端数据 单利类, 适配器

#ifndef __QingLibCocos2dx__StorageUtils__
#define __QingLibCocos2dx__StorageUtils__

#include "Common.h"

NS_QING_BEGIN

class StorageUtils
{
public:
	static StorageUtils * shared();
	void purge();
    
    /**显示xml位置*/
    void show();
    
    bool clearAll() { /**TODO: How clear All xml content ? */ return false; }
    
    /**
     * TODO: 怎样使用模板方法？来实现重载的方法？
     */
    
    
    /**
     * set 设置值
     * get value 是默认参数
     *
     */
    void set(string key, bool value);
    bool getBool(string key, bool value=false);
    
    
    void set(string key, int value);
    int getInt(string key, int value=0);
    
    
    void set(string key, float value);
    float getFloat(string key, float value=0.0f);
    
    
    void set(string key, double value);
    double getDouble(string key, double value=0.0f);
    
    /**
     * setString 不能写成set，否则会调用 set(key, bool) 这个函数
     */
    void setString(string key, string &value);
    string getString(string key, string value="");
    
    
protected:
    void flush();
    

private:
	StorageUtils();
	virtual ~StorageUtils();
	StorageUtils(const StorageUtils &);
    StorageUtils & operator=(const StorageUtils &);
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__StorageUtils__) */
