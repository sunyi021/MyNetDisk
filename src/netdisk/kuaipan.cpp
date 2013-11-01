#include "netdisk/kuaipan.h"
#include "http/http_connect.h"
#include <fstream>

MyErrorCode KuaiPan::GetSpaceInfo()
{
    return E_OK;
}

MyErrorCode KuaiPan::GetFileList(const std::string& strPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::GetFileInfo(const std::string strPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::DownLoadFile(const std::string strPath, const std::string& strFilePath)
{
    return E_OK;
}

MyErrorCode KuaiPan::UploadFile(const std::string strFilePath, const std::string& strPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::DeleteFile(const std::string strPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::MoveFile(const std::string strPath, const std::string strNewPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::CopyFile(const std::string strPath, const std::string strNewPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::CreateDir(const std::string strPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::DeleteDir(const std::string strPath)
{
    return E_OK;
}

MyErrorCode KuaiPan::MoveDir(const std::string strPath, const std::string strNewPath)
{
    return E_OK;
}