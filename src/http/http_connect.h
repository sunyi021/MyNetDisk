#ifndef HTTP_CONNECT_H
#define HTTP_CONNECT_H

#include "MyNetDisk.h"
#include <string>


class HttpRequest
{
public:
    enum RequestType
    {
        HTTP_GET = 0,
        HTTP_POST,
        HTTP_INVALID,
    };

public:
    RequestType m_eReqType;
    std::string m_strUrl;
    std::string m_strFormName;
    std::string m_strFormContent;
};

class HttpResponse
{
public:
    std::string m_strResponse;
};

class HttpConnect
{
private:
    HttpConnect();

    ~HttpConnect();

public:
    static MyErrorCode ProcessRequest(const HttpRequest& cReq, HttpResponse& cResponse);

private:
    static MyErrorCode ProcessPostRequest(const HttpRequest& cRequest, HttpResponse& cResponse);

    static MyErrorCode ProcessGetRequest(const HttpRequest& cRequest, HttpResponse& cResponse);

private:
    static HttpConnect s_cHttpConnect;
};

#endif // HTTP_CONNECT_H
