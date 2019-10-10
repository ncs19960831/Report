#ifndef UIDAYREPORT_H
#define UIDAYREPORT_H

#include <QDialog>
#include "dayreport.h"

namespace Ui {
class uidayreport;
}

class uidayreport : public QDialog
{
    Q_OBJECT

public:

    explicit uidayreport(QWidget *parent = nullptr);
    ~uidayreport();

    explicit uidayreport(DayReport * dayreport);
    bool GetStatus();
    DayReport *GetReport();
    void FinishReport();

    void ResetConnect();
private slots:

    void Accept();
    void Reject();
private:
    bool WriteOk;
    Ui::uidayreport *ui;
};

#endif // UIDAYREPORT_H
