//
//  FileUtils.h
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-6-5.
//
//
/// 简单文件操作 基于cocos2dx. 单利类

#ifndef __QingLibCocos2dx__FileUtils__
#define __QingLibCocos2dx__FileUtils__

#include "Common.h"

NS_QING_BEGIN

enum FILE_PATH_TYPE{
    
    FILE_PATH_TYPE_NONE = 0,
    ///
    FILE_PATH_TYPE_FULLPATH,
    ///可写路径
    FILE_PATH_TYPE_WRITABLE,
};

class FileUtils
{
public:
//	static FileUtils * shared();
//	void purge();
    
    
    /**返回文件的完整路径*/
    static string fullPathForFilename(const char* fileName);
    
    /**转化成可写目录的路径*/
    static string getWritablePath(const char* fileName);
    
    
    static void getPathByType(string& path, FILE_PATH_TYPE pathType);
    
    /**
     * 保存文件
     * @param pathType 根据类型添加路径 默认是writable路径
     */
    static bool save(string& path, string& data, FILE_PATH_TYPE pathType=FILE_PATH_TYPE_WRITABLE);
    
    /**
     * 加载文件
     * @param pathType 根据类型添加路径
     */
    static bool loadFile(string& path, string& strResult, FILE_PATH_TYPE pathType);
    
    /**
     * 读取zip的数据
     */
    static string getFileDataFromZip(string& strZipStream, string fileName);
    

private:
	FileUtils();
	virtual ~FileUtils();
	FileUtils(const FileUtils &);
    FileUtils & operator=(const FileUtils &);
};

NS_QING_END

#endif /* defined(__QingLibCocos2dx__FileUtils__) */
