#include "datamanage.h"
#include <QSqlDatabase>
#include <QSqlIndex>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QUuid>
#include <QTableView>
#include "dayreport.h"

QSqlDatabase      thisSqlDataBase;
QTableView*    thisTableView;
QSqlIndex           thisSqlIndex;
QSqlRecord thisSqlRecord;
QSqlQuery thisSqlQuery;


bool DataManage::InitSqlDataBase(QTableView* SqlTable,
                                 QString Database,
                                 QString DatabaseName,
                                 QString HostName,
                                 QString UserName,
                                 QString PassWord,
                                 int port)
{
    if (&thisSqlDataBase != nullptr)
    {
        if (thisSqlDataBase.isValid())
        {
            if (thisSqlDataBase.isOpen())
            {
                return true;
            }
        }
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
        QSqlQuery* SqlQuery = new QSqlQuery(MySqlDataBase);
        QString DayReportSql = "create table if not exists DayReport("
                          "[id] varchar primary key ,"
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
        thisSqlQuery = *SqlQuery;
        static QList<QString> list;
        retSqlTableModel->setTable("DayReport");//选择数据表
        retSqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
        list.clear();
        list<<\
               "ID"<<
               "序号"<<
               "机型"<<\
               "事项"<<\
               "目标"<<\
               "实际进行"<<\
               "差异及改善"<<\
               "开始时间"<<\
               "结束时间"<<\
               "权重"<<\
               "评估";
        retSqlTableModel->setHeaderData(0, Qt::Horizontal,list.at(0));
        retSqlTableModel->setHeaderData(1, Qt::Horizontal,list.at(1));
        retSqlTableModel->setHeaderData(2, Qt::Horizontal,list.at(2));
        retSqlTableModel->setHeaderData(3, Qt::Horizontal,list.at(3));
        retSqlTableModel->setHeaderData(4, Qt::Horizontal,list.at(4));
        retSqlTableModel->setHeaderData(5, Qt::Horizontal,list.at(5));
        retSqlTableModel->setHeaderData(6, Qt::Horizontal,list.at(6));
        retSqlTableModel->setHeaderData(7, Qt::Horizontal,list.at(7));
        retSqlTableModel->setHeaderData(8, Qt::Horizontal,list.at(8));
        retSqlTableModel->setHeaderData(9, Qt::Horizontal,list.at(9));
        retSqlTableModel->setHeaderData(10, Qt::Horizontal,list.at(10));
        retSqlTableModel->select(); //选取整个表的所有行
        SqlTable->setModel(retSqlTableModel);
        thisTableView = SqlTable;
        thisSqlDataBase = MySqlDataBase;
        return true;
    }
}


DataManage::DataManage(QTableView* SqlTable)
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

DataManage::~DataManage()
{
    thisSqlDataBase.close();
    thisSqlIndex.~QSqlIndex();
    thisSqlRecord.~QSqlRecord();
    thisSqlQuery.~QSqlQuery();

}

void DataManage::SaveDataBase(QString String)
{

}

//尝试加入当前日志参数
void DataManage::SetNewData(int Row,DayReport* DayReport)
{
    QString String,AddString;
    QSqlTableModel* SqlTableModel = (QSqlTableModel*)thisTableView->model();
    QSqlRecord SqlRecord = SqlTableModel->record();

    if (!DayReport->GetNumber(&String))
    {
        return;
    }
    Row--;
    DayReport->GetStartTime(&String);
    QUuid *Uuid = new QUuid(String);
    String=Uuid->createUuid().toString();

    SqlRecord.setValue(0,String);

    DayReport->GetNumber(&String);
    SqlRecord.setValue(1,String);

    DayReport->GetProduct(&String);
    SqlRecord.setValue(2,String);

    DayReport->GetCase(&String);
    SqlRecord.setValue(3,String);

    DayReport->GetTarget(&String);
    SqlRecord.setValue(4,String);

    DayReport->GetProcess(&String);
    SqlRecord.setValue(5,String);

    DayReport->GetDiff(&String);
    SqlRecord.setValue(6,String);

    DayReport->GetStartTime(&String);
    SqlRecord.setValue(7,String);

    DayReport->GetEndTime(&String);
    SqlRecord.setValue(8,String);

    DayReport->GetPriority(&String);
    SqlRecord.setValue(9,String);

    DayReport->GetEvaluate(&String);
    SqlRecord.setValue(10,String);


    SqlTableModel->insertRecord(Row,SqlRecord);
    Row = SqlTableModel->rowCount();
    SqlTableModel->submitAll();


}

//尝试加入当前日志参数
void DataManage::EditData(int Row,DayReport* DayReport)
{
    QString String,AddString;
    QSqlTableModel* SqlTableModel = (QSqlTableModel*)thisTableView->model();
    QSqlRecord SqlRecord = SqlTableModel->record(Row-1);

    if (!DayReport->GetNumber(&String))
    {
        return;
    }
    DayReport->GetStartTime(&String);
    QUuid *Uuid = new QUuid(String);
    String=Uuid->createUuid().toString();

    SqlRecord.setValue(0,String);

//    DayReport->GetNumber(&String);
    SqlRecord.setValue(1,QString(0x30+Row));

    DayReport->GetProduct(&String);
    SqlRecord.setValue(2,String);

    DayReport->GetCase(&String);
    SqlRecord.setValue(3,String);

    DayReport->GetTarget(&String);
    SqlRecord.setValue(4,String);

    DayReport->GetProcess(&String);
    SqlRecord.setValue(5,String);

    DayReport->GetDiff(&String);
    SqlRecord.setValue(6,String);

    DayReport->GetStartTime(&String);
    SqlRecord.setValue(7,String);

    DayReport->GetEndTime(&String);
    SqlRecord.setValue(8,String);

    DayReport->GetPriority(&String);
    SqlRecord.setValue(9,String);

    DayReport->GetEvaluate(&String);
    SqlRecord.setValue(10,String);

    if(SqlTableModel->setRecord(Row-1,SqlRecord))
    {
        Row = SqlTableModel->rowCount();
        SqlTableModel->submitAll();
    }

}


//尝试加入当前日志参数
void DataManage::DelData(int Row)
{
    QString String,AddString;
    QSqlTableModel* SqlTableModel = (QSqlTableModel*)thisTableView->model();
    QSqlRecord SqlRecord = SqlTableModel->record(Row-1);

    if (SqlRecord.isNull("ID"))
    {
        return;
    }
    if (SqlTableModel->rowCount() == Row)
        Row--;
    if(SqlTableModel->removeRow(Row))
    {
        Row = SqlTableModel->rowCount();
        SqlTableModel->submitAll();
    }
    else
    {
        SqlTableModel->revertAll(); //如果不删除，则撤销
    }

}


int DataManage::GetOneData(int Row, DayReport* DayReport)
{
    QString* String = new QString();
    QSqlRecord *SqlRecord = &thisSqlRecord;
    QSqlTableModel* SqlTableModel = (QSqlTableModel*)thisTableView->model();
    *SqlRecord = SqlTableModel->record(Row-1);

    *String = SqlRecord->value(1).toString();
    DayReport->SetNumber(*String);

    *String = SqlRecord->value(2).toString();
    DayReport->SetProduct(*String);

    *String = SqlRecord->value(3).toString();
    DayReport->SetCase(*String);

    *String = SqlRecord->value(4).toString();
    DayReport->SetTarget(*String);

    *String = SqlRecord->value(5).toString();
    DayReport->SetProcess(*String);

    *String = SqlRecord->value(6).toString();
    DayReport->SetDiff(*String);

    *String = SqlRecord->value(7).toString();
    DayReport->SetStartTime(*String);

    *String = SqlRecord->value(8).toString();
    DayReport->SetEndTime(*String);

    *String = SqlRecord->value(9).toString();
    DayReport->SetPriority(*String);

    *String = SqlRecord->value(10).toString();
    DayReport->SetEvaluate(*String);

}








