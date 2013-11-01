#include "netdisk/baidu_yun.h"
#include "http/http_connect.h"
#include <fstream>

#ifdef _DEBUG
#include <iostream>
#endif

const std::string API_KEY =     "UXTsm9M79DYzHk5KpEcUCZXB";
const std::string SECRET_KEY =  "CIFX3aMPyQHgN78xCCL2YOi6zLKb1Qfb";

const std::string ACCESS_TOKEN =    "access_token=3.4a4a6377dc7e9b068809d908b7ab857c.2592000.1385912193.1765001207-1634735";
const std::string SESSION_SECRET =  "411f9929275c558bf05717df49c9e29b";
const std::string SESSION_KEY =     "94qyUuTsyPchyJQ%2Fm7eTCOpxZT8EefkZydCZWRts6hqlO2Tj5zTBWBwZ0kMyL%2BrMztGHFDGf%2B207968Ctn1Px5FvZrutlopF";
const std::string SCOPE =           "basic";

static const std::string REST_URL = "https://c.pcs.baidu.com/rest/2.0/pcs/file";
static const std::string PATH = "path=/apps/MyNetDisk/";
static const std::string PARAM_DELIMITER = "&";
static const std::string CGI_DELIMITER =   "?";

MyErrorCode BaiduYun::GetSpaceInfo()
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://pcs.baidu.com/rest/2.0/pcs/quota
    // req: GET
    // param:
    //      method=info
    //      access_token=
    //////////////////////////////////////////////////////////////////////////()

    static const std::string SPACE_QUOTA = "https://pcs.baidu.com/rest/2.0/pcs/quota?method=info";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = SPACE_QUOTA + PARAM_DELIMITER
                        + ACCESS_TOKEN;
    cRequest.m_eReqType = HttpRequest::HTTP_GET;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}


MyErrorCode BaiduYun::GetFileList(const std::string& strPath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://pcs.baidu.com/rest/2.0/pcs/file
    // req: GET
    // param:
    //      method=list
    //      access_token=
    //      path=
    //////////////////////////////////////////////////////////////////////////()

    static const std::string FILE_LIST = "https://pcs.baidu.com/rest/2.0/pcs/file?method=list";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = FILE_LIST + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + strPath;
    cRequest.m_eReqType = HttpRequest::HTTP_GET;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}

MyErrorCode BaiduYun::GetFileInfo(const std::string strPath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: GET
    // param:
    //      method=meta
    //      access_token=
    //      path=
    //////////////////////////////////////////////////////////////////////////()

    static const std::string FILE_INFO = "https://c.pcs.baidu.com/rest/2.0/pcs/file?method=meta";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = FILE_INFO + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + strPath;
    cRequest.m_eReqType = HttpRequest::HTTP_GET;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}

MyErrorCode BaiduYun::DownLoadFile(const std::string strPath, const std::string& strFilePath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: GET
    // param:
    //      method=download
    //      access_token=
    //      path=
    // form:
    //      file
    //////////////////////////////////////////////////////////////////////////()

    static const std::string DOWNLOAD_FILE = "https://c.pcs.baidu.com/rest/2.0/pcs/file?method=download";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = DOWNLOAD_FILE + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + strPath;
    cRequest.m_eReqType = HttpRequest::HTTP_GET;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    if (0 != eResult)
    {
        return eResult;
    }

    // write file
    std::ofstream cFile;
    cFile.open(strFilePath.c_str());

    if (!cFile.is_open())
    {
        return E_LOCAL_FILE_NOT_EXISTED;
    }

    cFile.write(cResponse.m_strResponse.c_str(), cResponse.m_strResponse.size());
    cFile.close();
    
    return eResult;
}

MyErrorCode BaiduYun::UploadFile(const std::string strFilePath, const std::string& strPath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: POST
    // param:
    //      method=upload
    //      access_token=
    //      path=
    //      ondup=overwrite
    // list:
    //      file
    //////////////////////////////////////////////////////////////////////////()

    static const std::string UPLOAD_FILE = "https://c.pcs.baidu.com/rest/2.0/pcs/file?method=upload";
    static const std::string OVERWRITE = "ondup=overwrite";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = UPLOAD_FILE + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + strPath + PARAM_DELIMITER
                        + OVERWRITE;
    cRequest.m_strFormName = "file";
    cRequest.m_strFormContent = strFilePath;
    cRequest.m_eReqType = HttpRequest::HTTP_POST;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}

MyErrorCode BaiduYun::DeleteFile(const std::string strPath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: POST
    // param:
    //      method=delete
    //      access_token=
    //      path=
    //////////////////////////////////////////////////////////////////////////()

    static const std::string DELETE_FILE = "https://c.pcs.baidu.com/rest/2.0/pcs/file?method=delete";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = DELETE_FILE + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + strPath;
    cRequest.m_eReqType = HttpRequest::HTTP_POST;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}

MyErrorCode BaiduYun::MoveFile(const std::string strPath, const std::string strNewPath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: POST
    // param:
    //      method=move
    //      access_token=
    //      from=
    //      to=
    //////////////////////////////////////////////////////////////////////////()

    static const std::string DELETE_FILE = "https://c.pcs.baidu.com/rest/2.0/pcs/file?method=move";
    static const std::string FROM_PATH = "from=";
    static const std::string TO_PATH = "to=";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = DELETE_FILE + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + FROM_PATH + strPath + PARAM_DELIMITER
                        + PATH + TO_PATH + strNewPath;
    cRequest.m_eReqType = HttpRequest::HTTP_POST;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}

MyErrorCode BaiduYun::CopyFile(const std::string strPath, const std::string strNewPath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: POST
    // param:
    //      method=copy
    //      access_token=
    //      from=
    //      to=
    //////////////////////////////////////////////////////////////////////////()

    static const std::string DELETE_FILE = "https://c.pcs.baidu.com/rest/2.0/pcs/file?method=copy";
    static const std::string FROM_PATH = "from=";
    static const std::string TO_PATH = "to=";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = DELETE_FILE + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + FROM_PATH + strPath + PARAM_DELIMITER
                        + PATH + TO_PATH + strNewPath;
    cRequest.m_eReqType = HttpRequest::HTTP_POST;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}

MyErrorCode BaiduYun::CreateDir(const std::string strPath)
{
    //////////////////////////////////////////////////////////////////////////()
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: POST
    // param:
    //      method=mkdir
    //      access_token=
    //      path=
    //////////////////////////////////////////////////////////////////////////()

    static const std::string DELETE_FILE = "https://c.pcs.baidu.com/rest/2.0/pcs/file?method=mkdir";

    // initialize request
    HttpRequest cRequest;
    cRequest.m_strUrl = DELETE_FILE + PARAM_DELIMITER
                        + ACCESS_TOKEN + PARAM_DELIMITER
                        + PATH + strPath;
    cRequest.m_eReqType = HttpRequest::HTTP_POST;

    // get response
    HttpResponse cResponse;
    MyErrorCode eResult = HttpConnect::ProcessRequest(cRequest, cResponse);

    return eResult;
}

MyErrorCode BaiduYun::DeleteDir(const std::string strPath)
{
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: POST
    // param:
    //      method=delete
    //      access_token=
    //      path=

    return DeleteFile(strPath);
}

MyErrorCode BaiduYun::MoveDir(const std::string strPath, const std::string strNewPath)
{
    // url: https://c.pcs.baidu.com/rest/2.0/pcs/file
    // req: POST
    // param:
    //      method=move
    //      access_token=
    //      from=
    //      to=

    return MoveFile(strPath, strNewPath);
}
