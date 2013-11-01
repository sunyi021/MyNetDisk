#ifndef MYNETDISK_H
#define MYNETDISK_H

enum MyErrorCode
{
    E_OK = 0,

    // http connection
    E_CONNECTION_ERROR,
    E_INVALID_REQ,

    // remote file system
    E_REMOTE_FILE_NOT_EXISTED,
    E_REMOTE_FILE_ALREADY_EXISTED,

    // local file system
    E_LOCAL_FILE_NOT_EXISTED,
    E_LOCAL_FILE_ALREADY_EXISTED,
    E_OTHER,
};

#endif // MYNETDISK_H
