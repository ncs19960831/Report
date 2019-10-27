#ifndef UIDAYREPORT_H
#define UIDAYREPORT_H

#include <QComboBox>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include "dayreport.h"

namespace Ui {
class uidayreport;
}

class uidayreport : public QDialog
{
    Q_OBJECT

public:

    explicit uidayreport(QWidget *parent = nullptr);
    explicit uidayreport(int Index,QWidget *parent = nullptr);
    ~uidayreport();

    explicit uidayreport(DayReport * dayreport,int Index);
    bool GetStatus();
    DayReport *GetReport();
    void FinishReport();

    void SetSelectIndex(int Index);
    void ResetConnect();
    QString SelfRead(QDateTimeEdit *DateTime);

private slots:

    void Accept();
    void Reject();
private:
    bool WriteOk;
    Ui::uidayreport *ui;
    QString SelfRead(QLineEdit* InputString);
    QString SelfRead(QComboBox* InputString);
    QString SelfRead(QTextEdit* InputString);
};

#endif // UIDAYREPORT_H
