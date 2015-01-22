#include "coccipool.h"

COCCIPool::COCCIPool(Environment *env,const DB_USER_INFO& db_user_info):
    env_(nullptr), stateless_connection_pool_(nullptr)\
  , max_conn_(POOL_CONNECTION_MAX), min_conn_(POOL_CONNECTION_MIN)\
  , incr_conn_(POOL_CONNECTION_INC)
{
    if(nullptr != env)
    {
        env_ = env;
        dbname_ 		= db_user_info.dbname_;
        user_name_ 	= db_user_info.user_name_;
        password_ 		= db_user_info.password_;
    }
    int ret = CreateConnectionPool(dbname_,  user_name_, password_\
                         , max_conn_, min_conn_, incr_conn_);
    if(E_OCCI_OK != ret)
    {
        //log
    }
    else
    {
        //log
    }
}

COCCIPool::~COCCIPool()
{
    DestroyConnectionPool();
}

int COCCIPool::CreateConnectionPool(const string &dbname, string &username, string &password, unsigned int max_conn, unsigned int min_conn, unsigned int incr_conn)
{
    try
    {
        if (dbname.empty())
        {
            return E_OCCI_DB_NAME;
        }
        if (username.empty())
        {
            return E_OCCI_USER_NAME;
        }
        if (password.empty())
        {
            return E_OCCI_PASSWORD;
        }

        if (nullptr != stateless_connection_pool_)
        {
            return E_OCCI_OK;
        }
        else if (nullptr != env_)
        {
            stateless_connection_pool_  \
                    = env_->createStatelessConnectionPool(username\
            , password, dbname, max_conn, min_conn\
            , incr_conn, StatelessConnectionPool::HOMOGENEOUS);
            if (nullptr == stateless_connection_pool_)
            {
                return E_OCCI_C_OCCI_POOL;
            }
            else
            {
                stateless_connection_pool_->setTimeOut(900);
                //当连接都处于繁忙时, 再次取连接是强制得到
                StatelessConnectionPool::BusyOption busy_option\
                        = StatelessConnectionPool::FORCEGET;
                stateless_connection_pool_->setBusyOption(busy_option);
                return E_OCCI_OK;
            }
        }
    }
    catch (SQLException &e)
    {

    }
}

int COCCIPool::DestroyConnectionPool()
{
    try
    {
        if (nullptr != stateless_connection_pool_ && nullptr != env_)
        {
            env_->terminateStatelessConnectionPool(stateless_connection_pool_);
            stateless_connection_pool_ = nullptr;
            return E_OCCI_OK;
        }
    }
    catch (SQLException &e)
    {
    }
}

unsigned int COCCIPool::GetUsingConnectionCount() const
{
    return static_cast<unsigned int>(connection_list_.size());
}

unsigned int COCCIPool::GetOpenConnectionCount() const
{
   return stateless_connection_pool_->getOpenConnections();
}

Connection *COCCIPool::GetConnection()
{
    try
    {
        if (nullptr != stateless_connection_pool_)
        {
            if (0 >= stateless_connection_pool_->getOpenConnections())
            {
                return nullptr;
            }
            Connection* conn = stateless_connection_pool_->getConnection();
            //将其加入list中
            if (nullptr != conn)
            {
                connection_list_.push_back(conn);
            }
            return conn;
        }
        return nullptr;
    }
    catch (SQLException &e)
    {
        return nullptr;
    }
}

bool COCCIPool::ReleaseConnection(Connection *connection)
{
    try
    {
        if (nullptr != connection && nullptr != stateless_connection_pool_)
        {
            connection_list_.remove(connection);
            stateless_connection_pool_->releaseConnection(connection);
            connection = nullptr;
            return true;
        }
            return false;
    }
    catch(SQLException &e)
    {
        /*if (NULL != connection && NULL != stateless_connection_pool_)
        {
        stateless_connection_pool_->releaseConnection(connection);
        connection = NULL;
        return TRUE;
        }*/
        return false;
    }
}

