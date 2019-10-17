#include "datamanage.h"
#include "QSqlDatabase"
#include "QSqlQuery"

DataManage::DataManage()
{
    QSqlQuery SqlQuery;
    QSqlDatabase MySqlDataBase = QSqlDatabase::addDatabase("DayReport");

}
