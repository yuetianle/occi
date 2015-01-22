#ifndef CRECORD_H
#define CRECORD_H

#include <memory>
#include <vector>
#include <map>
#include "coccicommon.h"

class COCCIObj;
typedef struct _DATA_INFO
{
    string column_name_;
    string data_;
}DATA_INFO;
typedef vector<DATA_INFO> VECRecord;

typedef vector<VECRecord> RecordList;

class CRecord
{
public:
    CRecord();
    ~CRecord();
    friend class COCCIObj;
    unsigned int GetRowCount() const;

    string GetString(string column_name, unsigned int row_index);
    unsigned int getUInt(string column_name,unsigned int row_index);
    int getInt(string column_name,unsigned int row_index);
    float getFloat(string column_name,unsigned int row_index);

private:
    void AddRecord(unsigned int column_count, char **column_name, char **column_values);
    void SetRowCount(unsigned int row_count);

    RecordList record_list_;
    unsigned int row_count_;
};

#endif // CRECORD_H
