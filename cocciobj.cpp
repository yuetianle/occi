#include "cocciobj.h"

COCCIObj::COCCIObj(const DB_USER_INFO &db_user_info)
{
    Init();
    occi_pool_ = new COCCIPool(env_, db_user_info);
}

COCCIObj::~COCCIObj()
{
    if(nullptr != occi_pool_)
    {
        delete occi_pool_;
        occi_pool_ = nullptr;
    }
    Uninit();
}

bool COCCIObj::Init()
{
    try
    {
        if (nullptr != env_)
        {
            return true;
        }
        else
        {
            env_ = Environment::createEnvironment(Environment::THREADED_MUTEXED);
            if(nullptr == env_)
            {
                return false;
            }
            else
            {
//#if (OCCI_MAJOR_VERSION >9)
//            env_->setCacheSortedFlush(true);
//#endif
                return true;
            }
        }
    }
    catch (SQLException* e)
    {
        //cout<<e->getErrorCode()<<e->getMessage();
    }
}

void COCCIObj::Uninit()
{
   if (nullptr == env_)
   {
       return ;
   }
   else
   {
       Environment::terminateEnvironment(env_);
       return ;
   }
}

bool COCCIObj::Query(const string &cmd, CRecord *result)
{
    bool is_ok = CheckQueryCmd(cmd);
//    is_ok?:return false;
    Connection *connect = occi_pool_->GetConnection();
    if (nullptr == connect)
    {
        return false;
    }

    Statement* statement = connect->createStatement();
    if (nullptr == statement)
    {
        if (nullptr != connect)
        {
            occi_pool_->ReleaseConnection(connect);
        }
        return false;
    }

    statement->setSQL(cmd);
    ResultSet* result_set = nullptr;
    result_set = statement->executeQuery();

    if (nullptr != result_set)
    {
        vector<MetaData> table_column = result_set->getColumnListMetaData();
        int column_count = table_column.size();
        vector<int>		table_column_type;
        vector<string>		table_column_name;
        vector<int>		table_column_size;
        vector<int>		table_column_length;

        char** all_column_name = new char*[column_count];
        char** all_column_values = new char*[column_count];

        //*count = column_count;
        //查询结果集 列信息写入
        vector<MetaData>::iterator table_column_iter= table_column.begin();
        for (int index = 0; table_column_iter != table_column.end(); ++table_column_iter)
        {
            string name = table_column_iter->getString(MetaData::ATTR_NAME).c_str();
            table_column_name.push_back(name);
            int type = table_column_iter->getInt(MetaData::ATTR_DATA_TYPE);
            table_column_type.push_back(type);
            int size = table_column_iter->getInt(MetaData::ATTR_DATA_SIZE);
            table_column_size.push_back(size);

            all_column_values[index] 	= new char[size];
            all_column_name[index]	= new char[name.length()];
            memset(all_column_values[index], 0, size);
            memset(all_column_name[index], 0, name.length());
            memcpy(all_column_name[index], name.c_str(), name.length());
            index++;
        }
        for(int i=0; i < column_count; i++)
        {
        result_set->setCharacterStreamMode(i+1, CHAR_MAX_STREAM_SIZE);
        }
        //按行进行数据的提取
        char buff[10000];
        memset(buff, 0, 10000);
        unsigned int search_count = 0;

        while(ResultSet::END_OF_FETCH != result_set->next())
        {
            for(unsigned int index=0; index < column_count; index++)
            {
                Stream* stream= result_set->getStream(index+1);
                int one_row_length;//一条记录的总长度
                int length = 0;//一条记录中在某列的数据长度
                while(Stream::READY_FOR_READ == stream->status())
                {
                    const unsigned int read_size = 1000;
                    length = stream->readBuffer(buff+length,read_size);
                    one_row_length += length;
                    memcpy(all_column_values[index], buff, length);
                }
                result_set->closeStream(stream);

                memset(buff, 0, sizeof(buff));//清空buff变量
            }
            //
           result->AddRecord(column_count, all_column_name, all_column_values);
            /*if(nullptr != record)
            {
                record->addRecord(column_count, (const char**)all_column_name, (const char**)all_column_values);
            }*/
            search_count++;
        }
       result->SetRowCount(search_count);
        for(int index=0; index < column_count; index++)
        {
            if(nullptr != all_column_name)
            {
                delete []all_column_name[index];
                all_column_name[index] = nullptr;
            }
            if(nullptr != all_column_values)
            {
                delete []all_column_values[index];
                all_column_values[index] = nullptr;
            }
        }
        if (nullptr != all_column_name)
        {
            delete []all_column_name;
            all_column_name = nullptr;
        }
        if (nullptr != all_column_values)
        {
            delete []all_column_values;
            all_column_values = nullptr;
        }

        if (nullptr != statement && nullptr != connect)
        {
            connect->terminateStatement(statement);
            statement = nullptr;
        }
        if (nullptr != connect)
        {
            occi_pool_->ReleaseConnection(connect);
            connect = nullptr;
        }
    }
}

bool COCCIObj::CheckQueryCmd(const string &cmd)
{
   return true;
}
