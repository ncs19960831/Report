#include "dayreport.h"


DayReport::DayReport(QObject *parent) : QObject(parent)
{
    OnceDay.Case = "";
    OnceDay.Diff = "";
    OnceDay.Number = nullptr;
    OnceDay.Target = "";
    OnceDay.EndTime = "";
    OnceDay.Process = "";
    OnceDay.Product = "";
    OnceDay.Evaluate = "";
    OnceDay.Priority = "";
    OnceDay.StartTime = "";
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
QString StartTime,  //开始时间
QString EndTime,    //结束时间
QString Priority,   //权重（优先级）
QString Evaluate, //评估
QString Number)     //序号
{
    if (Number.isNull())
    {
        return;
    }
    else {
        OnceDay.Case = Case;
        OnceDay.Diff = Diff;
        OnceDay.Number = Number;
        OnceDay.Target = Target;
        OnceDay.EndTime = EndTime;
        OnceDay.Process = Process;
        OnceDay.Product = Product;
        OnceDay.Evaluate = Evaluate;
        OnceDay.Priority = Priority;
        OnceDay.StartTime = StartTime;
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
bool DayReport::GetNember(QString* string)
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
        OnceDay.Product = string;
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
        OnceDay.Product = string;
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
        OnceDay.Product = string;
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
        OnceDay.Product = string;
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
bool DayReport::SetStartTime(QString string)
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
bool DayReport::GetStartTime(QString* string)
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

bool DayReport::SetEndTime(QString string)
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
bool DayReport::GetEndTime(QString* string)
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
        OnceDay.Product = string;
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
        OnceDay.Product = string;
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



