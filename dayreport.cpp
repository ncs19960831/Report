#include "dayreport.h"


DayReport::DayReport(QObject *parent) : QObject(parent)
{
    QDate* DateNormal = new QDate(2000,1,1);
    QTime* TimeNormal = new QTime(1,1,1,0);
    QDateTime* DateTimeNormal =new QDateTime(DateNormal->currentDate(),TimeNormal->currentTime());

    OnceDay.Case = "";
    OnceDay.Diff = "";
    OnceDay.Number = nullptr;
    OnceDay.Target = "";
    OnceDay.EndTime = DateTimeNormal->currentDateTime();
    OnceDay.Process = "";
    OnceDay.Product = "";
    OnceDay.Evaluate = "";
    OnceDay.Priority = "";
    OnceDay.StartTime = DateTimeNormal->currentDateTime();
}
DayReport::DayReport(QString number)
{
    OnceDay.Number = number;
}

DayReport::DayReport(QString Product,    //机型
QString Case,       //事项
QString Target,     //目标
QString Process,    //实际进行
QString Diff,       //差异以及改善
QDateTime StartTime,  //开始时间
QDateTime EndTime,    //结束时间
QString Priority,   //权重（优先级）
QString Evaluate, //评估
QString Number)     //序号
{
    QDate* DateNormal = new QDate(2000,1,1);
    QTime* TimeNormal = new QTime(1,1,1,0);
    QDateTime* DateTimeNormal =new QDateTime(DateNormal->currentDate(),TimeNormal->currentTime());

    if (Number.isNull())
    {
        return;
    }
    else {
        OnceDay.Case = Case;
        OnceDay.Diff = Diff;
        OnceDay.Number = Number;
        OnceDay.Target = Target;
        OnceDay.EndTime = DateTimeNormal->currentDateTime();
        OnceDay.Process = Process;
        OnceDay.Product = Product;
        OnceDay.Evaluate = Evaluate;
        OnceDay.Priority = Priority;
        OnceDay.StartTime = DateTimeNormal->currentDateTime();
    }
}

bool DayReport::SetNumber(QString string)
{
    if (OnceDay.Number.isNull())
    {
        OnceDay.Number = string;
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetNumber(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Number;
        return true;
    }else
    {
        return false;
    }

}

bool DayReport::SetProduct(QString string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.Product = string;
        return true;
    }
    else {
        return false;
    }

}
bool DayReport::GetProduct(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Product;
        return true;
    }else
    {
        return false;
    }
}

bool DayReport::SetCase(QString string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.Case = string;
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetCase(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Case;
        return true;
    }else
    {
        return false;
    }
}

bool DayReport::SetTarget(QString string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.Target = string;
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetTarget(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Target;
        return true;
    }else
    {
        return false;
    }
}

bool DayReport::SetProcess(QString string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.Process = string;
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetProcess(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Process;
        return true;
    }else
    {
        return false;
    }
}

bool DayReport::SetDiff(QString string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.Diff = string;
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetDiff(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Diff;
        return true;
    }else
    {
        return false;
    }
}
bool DayReport::SetStartTime(QDateTime * string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.StartTime = string->currentDateTime();
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetStartTime(QDateTime* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.StartTime;
        return true;
    }else
    {
        return false;
    }
}

bool DayReport::SetEndTime(QDateTime * string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.EndTime = string->currentDateTime();
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetEndTime(QDateTime* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.EndTime;
        return true;
    }else
    {
        return false;
    }
}

bool DayReport::SetPriority(QString string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.Priority = string;
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetPriority(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Priority;
        return true;
    }else
    {
        return false;
    }
}

bool DayReport::SetEvaluate(QString string)
{
    if (!OnceDay.Number.isNull())
    {
        OnceDay.Evaluate = string;
        return true;
    }
    else {
        return false;
    }
}
bool DayReport::GetEvaluate(QString* string)
{
    if (!OnceDay.Number.isNull())
    {
        string = &OnceDay.Evaluate;
        return true;
    }else
    {
        return false;
    }
}



