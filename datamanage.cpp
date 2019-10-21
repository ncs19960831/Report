#include "datamanage.h"
#include <QSqlDatabase>
#include <QSqlIndex>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QUuid>
#include "dayreport.h"

QSqlDatabase      thisSqlDataBase;
QSqlTableModel*    thisSqlTableModel;
QSqlIndex           thisSqlIndex;
QSqlRecord thisSqlRecord;

bool DataManage::InitSqlDataBase(QWidget* SqlTable,
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
    QSqlTableModel* retSqlTableModel = new QSqlTableModel(SqlTable,MySqlDataBase);

    MySqlDataBase.setDatabaseName(DatabaseName);
    MySqlDataBase.setHostName(HostName);
    MySqlDataBase.setUserName(UserName);
    MySqlDataBase.setPassword(PassWord);
    MySqlDataBase.setPort(port);

    if (MySqlDataBase.open() == true)
    {
        thisSqlDataBase = MySqlDataBase;
        thisSqlTableModel = retSqlTableModel;
        return true;
    }
}


DataManage::DataManage(QWidget* SqlTable)
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

//尝试加入当前日志参数
void DataManage::SetNewData(int Row,DayReport DayReport)
{
    QString String,AddString;
    QSqlTableModel* SqlTableModel = thisSqlTableModel;
    QSqlRecord SqlRecord = SqlTableModel->record();

    if (!DayReport.GetNumber(&String))
    {
        return;
    }
    DayReport.GetStartTime(&String);
    QUuid *Uuid = new QUuid(String);
    SqlRecord.setValue(Row+1,Uuid->toString());
    SqlTableModel->insertRecord(Row+1,SqlRecord);
    SqlTableModel->submitAll();


}
