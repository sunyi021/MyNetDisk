#include "MyNetDisk.h"
#include "http/http_connect.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

HttpConnect HttpConnect::s_cHttpConnect;

static size_t WriteFunction(void *ptr,  size_t  size,  size_t  nmemb,  void *stream)
{
    if (NULL == stream)
    {
        return 0;
    }

    std::string* pcString = (std::string*)stream;

    pcString->assign((char*)ptr, size * nmemb);

    return size * nmemb;
}


HttpConnect::HttpConnect()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

HttpConnect::~HttpConnect()
{
    curl_global_cleanup();
}

MyErrorCode HttpConnect::ProcessRequest(const HttpRequest& cRequest, HttpResponse& cResponse)
{
    MyErrorCode eResult = E_INVALID_REQ;

    switch (cRequest.m_eReqType)
    {
    case HttpRequest::HTTP_GET:
        eResult = ProcessGetRequest(cRequest, cResponse);
        break;

    case HttpRequest::HTTP_POST:
        eResult = ProcessPostRequest(cRequest, cResponse);
        break;

    default:
        eResult = E_INVALID_REQ;
        break;
    }

#ifdef _DEBUG
    std::cout
        << "Request url:" << std::endl
        << "\t" << cRequest.m_strUrl << std::endl
        << "Response:" << std::endl
        << "\t" << cResponse.m_strResponse << std::endl << std::endl;
#endif

    return eResult;
}

MyErrorCode HttpConnect::ProcessPostRequest(const HttpRequest& cRequest, HttpResponse& cResponse)
{    
    // initial request
    CURL *pcCurl;
    CURLcode eResult;

    pcCurl = curl_easy_init();

    if (NULL == pcCurl)
    {
        return E_CONNECTION_ERROR;
    }

    // initial form
    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist=NULL;

    if (!cRequest.m_strFormName.empty())
    {
        /* Fill in the file upload field */
        curl_formadd(   &formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, cRequest.m_strFormName.c_str(),
                        CURLFORM_FILE, cRequest.m_strFormContent.c_str(),
                        CURLFORM_END);

        curl_easy_setopt(pcCurl, CURLOPT_HTTPPOST, formpost);
    }
    else
    {
        // set post
        curl_easy_setopt(pcCurl, CURLOPT_POST, 1L);
    }

    // set url to visit
    curl_easy_setopt(pcCurl, CURLOPT_URL, cRequest.m_strUrl.c_str());

    // set callback function and return data
    curl_easy_setopt(pcCurl, CURLOPT_WRITEFUNCTION, WriteFunction);
    curl_easy_setopt(pcCurl, CURLOPT_WRITEDATA, &cResponse.m_strResponse);

    // enable ssl mode
    curl_easy_setopt(pcCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(pcCurl, CURLOPT_SSL_VERIFYHOST, 0L);


    // perform request
    eResult = curl_easy_perform(pcCurl);

    if (CURLE_OK != eResult)
    {
        return E_CONNECTION_ERROR;
    }

    curl_easy_cleanup(pcCurl);

    return E_OK;
}

MyErrorCode HttpConnect::ProcessGetRequest(const HttpRequest& cRequest, HttpResponse& cResponse)
{
    // initial request
    CURL *pcCurl;
    CURLcode eResult;

    pcCurl = curl_easy_init();

    if (NULL == pcCurl)
    {
        return E_CONNECTION_ERROR;
    }

    // set url to visit
    curl_easy_setopt(pcCurl, CURLOPT_URL, cRequest.m_strUrl.c_str());

    // set callback function and return data
    curl_easy_setopt(pcCurl, CURLOPT_WRITEFUNCTION, WriteFunction);
    curl_easy_setopt(pcCurl, CURLOPT_WRITEDATA, &cResponse.m_strResponse);

    // enable ssl mode
    curl_easy_setopt(pcCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(pcCurl, CURLOPT_SSL_VERIFYHOST, 0L);

    // set get
    curl_easy_setopt(pcCurl, CURLOPT_HTTPGET, 1L);

    // perform request
    eResult = curl_easy_perform(pcCurl);

    if (CURLE_OK != eResult)
    {
        return E_CONNECTION_ERROR;
    }

    curl_easy_cleanup(pcCurl);

    return E_OK;
}
