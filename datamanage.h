#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include "dayreport.h"

#include <QSqlQuery>
#include <QTableView>
#include <QWidget>



class DataManage
{
public:

    QSqlQuery InitSqlDataBase(QSqlDatabase SqlDataBase);
    bool InitSqlDataBase(QTableView *SqlTable, QString Database, QString DatabaseName, QString HostName, QString UserName, QString PassWord, int port);
    DataManage(QTableView* SqlTable);
    void SaveDataBase(QString String);
    void SetNewData(int Row, DayReport* DayReport);
    int GetOneData(int Row, DayReport *DayReport);
    void EditData(int Row, DayReport *DayReport);
private:
    ~DataManage();
};

#endif // DATAMANAGE_H
