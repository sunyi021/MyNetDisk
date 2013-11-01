#ifndef BAIDU_YUN_H
#define BAIDU_YUN_H

#include "netdisk/netdisk.h"

class BaiduYun : public NetDisk
{
public:
    BaiduYun()
    {

    }

    virtual ~BaiduYun()
    {

    }

    // file info
    virtual MyErrorCode GetSpaceInfo();

    virtual MyErrorCode GetFileList(const std::string& strPath);

    virtual MyErrorCode GetFileInfo(const std::string strPath);

    // file operations
    virtual MyErrorCode DownLoadFile(const std::string strPath, const std::string& strFilePath);

    virtual MyErrorCode UploadFile(const std::string strFilePath, const std::string& strPath);

    virtual MyErrorCode DeleteFile(const std::string strPath);

    virtual MyErrorCode MoveFile(const std::string strPath, const std::string strNewPath);

    virtual MyErrorCode CopyFile(const std::string strPath, const std::string strNewPath);

    // directory operations
    virtual MyErrorCode CreateDir(const std::string strPath);

    virtual MyErrorCode DeleteDir(const std::string strPath);

    virtual MyErrorCode MoveDir(const std::string strPath, const std::string strNewPath);

private:
};

#endif // BAIDU_YUN_H
