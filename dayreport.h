#ifndef DAYREPORT_H
#define DAYREPORT_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QDateTime>




class DayReport : public QObject
{
    Q_OBJECT
public:
    struct Day
    {
        QString Number;     //序号
        QString Product;    //机型
        QString Case;       //事项
        QString Target;     //目标
        QString Process;    //实际进行
        QString Diff;       //差异以及改善
        QDateTime StartTime;  //开始时间
        QDateTime EndTime;    //结束时间
        QString Priority;   //权重（优先级）
        QString Evaluate;   //评估
    };
    explicit DayReport(QObject *parent = nullptr);
    explicit DayReport(Day DayReport);

    explicit DayReport(QString number);

    explicit DayReport( QString Product, QString Case, QString Target, QString Process, QString Diff, QDateTime StartTime, QDateTime EndTime, QString Priority, QString Evaluate,QString Number = nullptr);    bool SetNumber(QString string);
    bool GetNumber(QString* string);
    bool SetProduct(QString string);
    bool GetProduct(QString* string);
    bool SetCase(QString string);
    bool GetCase(QString* string);
    bool SetTarget(QString string);
    bool GetTarget(QString* string);
    bool SetProcess(QString string);
    bool GetProcess(QString* string);
    bool SetDiff(QString string);
    bool GetDiff(QString* string);
    bool SetStartTime(QDateTime * string);
    bool GetStartTime(QString* string);
    bool SetEndTime(QDateTime * string);
    bool GetEndTime(QString* string);
    bool SetPriority(QString string);
    bool GetPriority(QString* string);
    bool SetEvaluate(QString string);
    bool GetEvaluate(QString* string);

signals:

protected:
    Day OnceDay;

public slots:
};

#endif // DAYREPORT_H
