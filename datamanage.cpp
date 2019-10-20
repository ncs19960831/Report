#include "datamanage.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlTableModel>
#include <QUuid>
#include "dayreport.h"

QSqlDatabase      thisSqlDataBase;
QSqlTableModel*    thisSqlTableModel;



bool DataManage::InitSqlDataBase(QWidget SqlTable,
                                 QString Database,
                                 QString DatabaseName,
                                 QString HostName,
                                 QString UserName,
                                 QString PassWord,
                                 int port)
{
    if (!thisSqlDataBase.isOpen())
    {
        return true;
    }
    QSqlDatabase MySqlDataBase = QSqlDatabase::addDatabase(Database);
    QSqlTableModel* retSqlTableModel = new QSqlTableModel(&SqlTable,MySqlDataBase);
    MySqlDataBase.setDatabaseName(DatabaseName);

    MySqlDataBase.setHostName(HostName);
    MySqlDataBase.setUserName(UserName);
    MySqlDataBase.setPassword(PassWord);
    MySqlDataBase.setPort(20000);

    if (MySqlDataBase.open() == true)
    {
        thisSqlDataBase = MySqlDataBase;
        thisSqlTableModel = retSqlTableModel;
        return true;
    }
}

DataManage::

void DataManage::DataManage(QWidget SqlTable)
{

    if (InitSqlDataBase(SqlTable,
                    "DayReport",
                    "DayReport.db",
                    "NCSData",
                    "ncs",
                    "c^9%$27fiF274Dfg8@24!tcS8gvrr",
                    20000))
    {


    }
    else {
        return;
    }

}

void DataManage::SaveDataBase(QString String)
{

}

void DataManage::SetOneData(DayReport DayReport)
{
    QString String;
    QSqlTableModel SqlTableModel = thisSqlTableModel;
    if (!SqlTableModel.isValid() )
    {
        return;
    }
    if (!DayReport.GetNumber(&String))
    {
        return;
    }
    DayReport.GetStartTime(&String);
    QUuid *Uuid = new QUuid(String);

}
