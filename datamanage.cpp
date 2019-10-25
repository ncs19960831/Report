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
    if (thisSqlDataBase.isOpen())
    {
        return true;
    }
    QSqlDatabase MySqlDataBase = QSqlDatabase::addDatabase(Database);

    MySqlDataBase.setDatabaseName(DatabaseName);
    MySqlDataBase.setHostName(HostName);
    MySqlDataBase.setUserName(UserName);
    MySqlDataBase.setPassword(PassWord);
    MySqlDataBase.setPort(port);

    if (MySqlDataBase.open() == true)
    {
        QSqlTableModel* retSqlTableModel = new QSqlTableModel(SqlTable,MySqlDataBase);
        thisSqlDataBase = MySqlDataBase;
        QSqlQuery* SqlQuery = new QSqlQuery(MySqlDataBase);
        QString DayReportSql = "create table if not exists DayReport("
                          "[id] integer primary key autoincrement,"
                          "[Number] varchar(30),"       //序号
                          "[Product] varchar(30),"      //机型
                          "[Case] varchar(30),"         //事项
                          "[Target] varchar(30),"       //目标
                          "[Process] varchar(30),"      //实际进行
                          "[Diff] varchar(30),"         //差异以及改善
                          "[StartTime] varchar(30),"    //开始时间
                          "[EndTime] varchar(30),"      //结束时间
                          "[Priority] varchar(30),"     //权重（优先级）
                          "[Evaluate] varchar(30)"      //评估
                          ")";
        if(!(SqlQuery->exec(DayReportSql)))
            return false;
        thisSqlTableModel = retSqlTableModel;
//        MySqlDataBase.close();
        return true;
    }
}


DataManage::DataManage(QWidget* SqlTable)
{

    if (InitSqlDataBase(SqlTable,
                    "QSQLITE",
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
void DataManage::SetNewData(int Row,DayReport* DayReport)
{
    QString String,AddString;
    QSqlTableModel* SqlTableModel = thisSqlTableModel;
    QSqlRecord SqlRecord = SqlTableModel->record();

    if (!DayReport->GetNumber(&String))
    {
        return;
    }
    DayReport->GetStartTime(&String);
    QUuid *Uuid = new QUuid(String);
    SqlRecord.setValue(1,Uuid->toString());

    DayReport->GetNumber(&String);
    SqlRecord.setValue(2,String);

    DayReport->GetProduct(&String);
    SqlRecord.setValue(3,String);

    DayReport->GetCase(&String);
    SqlRecord.setValue(4,String);

    DayReport->GetTarget(&String);
    SqlRecord.setValue(5,String);

    DayReport->GetProcess(&String);
    SqlRecord.setValue(6,String);

    DayReport->GetDiff(&String);
    SqlRecord.setValue(7,String);

    DayReport->GetStartTime(&String);
    SqlRecord.setValue(8,String);

    DayReport->GetEndTime(&String);
    SqlRecord.setValue(9,String);

    DayReport->GetPriority(&String);
    SqlRecord.setValue(10,String);

    DayReport->GetEvaluate(&String);
    SqlRecord.setValue(11,String);


    SqlTableModel->insertRecord(Row+1,SqlRecord);
    Row = SqlTableModel->rowCount();
    SqlTableModel->submitAll();

}










