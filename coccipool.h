#ifndef COCCIPOOL_H
#define COCCIPOOL_H
#include <list>
#include "coccicommon.h"


class COCCIPool
{
public:
    COCCIPool(Environment *env,const DB_USER_INFO& db_user_info);
    ~COCCIPool();

/**
* @brief get a connection from a pool.
* @return
*/
    Connection* GetConnection();
/**
* @brief put back a connection into a pool.
* @return
*/
    bool ReleaseConnection(Connection *connection);
private:
/**
* @brief create a connection pool.
* @param [in]dbname [in]username [in]password [in]max_conn\
* [in]min_conn [in]incr_conn
* @return
*/
    int CreateConnectionPool(const string &dbname, string& username\
                             , string& password, unsigned int max_conn = 1\
            , unsigned int min_conn = 0, unsigned int incr_conn = 1);
/**
* @brief destroy a connection pool.
* @return
*/
    int DestroyConnectionPool();
/**
* @brief get using connection count.
* @return
*/
    unsigned int GetUsingConnectionCount() const;
/**
* @brief connection counts of a pool.
* @return
*/
    unsigned int GetOpenConnectionCount() const;

private:
    Environment *env_;/**<occi 环境变量*/
    StatelessConnectionPool *stateless_connection_pool_;/**<无状态连接池*/
    ConnectionPool *connection_pool_;/**<连接池*/

    string dbname_;/**<数据库名称*/
    string user_name_;/**<数据库用户名*/
    string password_;/**<数据库连接密码*/
    unsigned int max_conn_;/**<数据库最大连接数*/
    unsigned int min_conn_;/**<数据库最小连接数*/
    unsigned int incr_conn_;/**<每次增长个数*/
    list<Connection*> connection_list_/**<正在使用的连接列表*/;
};

#endif // COCCIPOOL_H
