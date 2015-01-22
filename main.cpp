#include <iostream>
#include "cocciobj.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    DB_USER_INFO db_user_info;
    string username = "ctuni_pub";
    string password = "ctunipub";
    string host 	= "10.95.3.101:1521/ctestsrc";
    db_user_info.dbname_ = host;
    db_user_info.ip_ = "10.95.3.101";
    db_user_info.port_ = 1521;
    db_user_info.user_name_ = username;
    db_user_info.password_ = password;
    COCCIObj *db_op = new COCCIObj(db_user_info);
    string cmd = "select * from data_type_def";
    db_op->Query(cmd,nullptr);
    return 0;
}

