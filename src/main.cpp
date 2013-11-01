#include "netdisk/baidu_yun.h"

int main(int argc, char **argv)
{
    BaiduYun cBaidu;
    cBaidu.GetFileList("");
    cBaidu.GetSpaceInfo();
    cBaidu.UploadFile("C:\\test.txt", "test.txt");
    cBaidu.DownLoadFile("test.txt", "D:\\test.txt");
    cBaidu.GetFileInfo("test.txt");

    return 0;
}
