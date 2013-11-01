#ifndef NETDISK_H
#define NETDISK_H

#include "MyNetDisk.h"
#include <string>

class NetDisk
{
public:
    NetDisk()
    {
    }

    virtual ~NetDisk()
    {
    }

    virtual bool Initialize()
    {
        return true;
    }

    // file info
    virtual MyErrorCode GetSpaceInfo() = 0;

    virtual MyErrorCode GetFileList(const std::string& strPath) = 0;

    virtual MyErrorCode GetFileInfo(const std::string strPath) = 0;

    // file operations
    virtual MyErrorCode DownLoadFile(const std::string strPath, const std::string& strFilePath) = 0;

    virtual MyErrorCode UploadFile(const std::string strFilePath, const std::string& strPath) = 0;

    virtual MyErrorCode DeleteFile(const std::string strPath) = 0;

    virtual MyErrorCode MoveFile(const std::string strPath, const std::string strNewPath) = 0;

    virtual MyErrorCode CopyFile(const std::string strPath, const std::string strNewPath) = 0;

    // directory operations
    virtual MyErrorCode CreateDir(const std::string strPath) = 0;

    virtual MyErrorCode DeleteDir(const std::string strPath) = 0;

    virtual MyErrorCode MoveDir(const std::string strPath, const std::string strNewPath) = 0;

};

#endif // NETDISK_H
