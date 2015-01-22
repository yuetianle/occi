#ifndef COCCIOBJ_H
#define COCCIOBJ_H


#include <memory>
#include <cstring>
#include "crecord.h"
#include "coccicommon.h"
#include "coccipool.h"

/**
* @brief 数据库单个对象.
* 数据库初始化、插入、查询、删除等操作
 */

class COCCIObj
{
    public:
        COCCIObj(const DB_USER_INFO &db_user_info);
        virtual ~COCCIObj();

/**
* @brief 初始化occi-API.
* @warning 调用occi初始化函数、调用一次
*/
        bool Init();
/**
* @brief 反初始化occi-API.
* @warning 调用occi初始化函数、调用一次
*/
        void Uninit();
        bool Query(const string&cmd,  CRecord *result);
        bool Insert(const string&cmd,  void* data);
        bool Delete(const string&cmd);
/**
*
*/
    protected:
/**
* @brief 查询字符串格式是否正确.
* @param [in] cmd
*/
    bool CheckQueryCmd(const string&cmd);
    private:
        DB_USER_INFO db_user_info_; /**< 数据库用户配置信息*/
        string cmd; /**< 完整命令语句*/
        Environment *env_;
        COCCIPool *occi_pool_;
};

#endif // COCCIOBJ_H
