#include "crecord.h"

CRecord::CRecord()
{

}

CRecord::~CRecord()
{

}

unsigned int CRecord::GetRowCount() const
{
    return row_count_;
}

string CRecord::GetString(string column_name, unsigned int row_index)
{
   if(record_list_.empty() || row_index > record_list_.size())
   {
       return "";
   }
   else
   {
        VECRecord record = record_list_.at(row_index -1);
        VECRecord::const_iterator iter_record_data = record.begin();
        for(; iter_record_data != record.end(); ++iter_record_data)
        {
            if(column_name == iter_record_data->column_name_)
            {
                return iter_record_data->data_;
            }
        }
        return "";
   }
}

void CRecord::AddRecord(unsigned int column_count, char **column_name, char **column_values)
{
    if(0 > column_count || nullptr == column_name || nullptr == column_values)
    {
        return;
    }
    VECRecord record;
    for (unsigned int index = 0; index < column_count; index++)
    {
        DATA_INFO data;
        data.column_name_ = column_name[index];
        data.data_ = column_values[index];
        record.push_back(data);
    }
    record_list_.push_back(record);
}

void CRecord::SetRowCount(unsigned int row_count)
{
    row_count_ = row_count;
}

