#ifndef COCCICOMMON_H
#define COCCICOMMON_H

#include <iostream>
#include <cstring>

#include "occi.h"
#include "occiCommon.h"
#include "occiData.h"
#include "occiObjects.h"
#include "occiAQ.h"
#include "occiControl.h"

using namespace std;
using namespace oracle::occi;

class COCCICommon
{
public:
    COCCICommon();
    ~COCCICommon();
};
typedef struct _DB_USER_INFO
{
    string user_name_;
    string password_;
    string dbname_;
    string ip_;
    uint32_t port_;
    _DB_USER_INFO()
    {
        port_ = 0;
    }
}DB_USER_INFO;


const unsigned int POOL_CONNECTION_MAX = 50;
const unsigned int POOL_CONNECTION_MIN = 5;
const unsigned int POOL_CONNECTION_INC  = 5;

const unsigned int CHAR_MAX_STREAM_SIZE = 1000000;
/**
* @brief Error Define
*/
enum DB_OCCI_ERROR
{
    E_OCCI_OK = 0,
    E_OCCI_ERROR = -1,
    E_OCCI_DB_NAME = -1026,
    E_OCCI_USER_NAME = -1024,
    E_OCCI_PASSWORD = -1022,
    E_OCCI_C_OCCI_POOL = -1020
};
#endif // COCCICOMMON_H
