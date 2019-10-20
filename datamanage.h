#ifndef DATAMANAGE_H
#define DATAMANAGE_H


class DataManage
{
public:
    DataManage();
    QSqlQuery InitSqlDataBase(QSqlDatabase SqlDataBase);
};

#endif // DATAMANAGE_H
