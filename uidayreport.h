#ifndef UIDAYREPORT_H
#define UIDAYREPORT_H

#include <QDialog>

namespace Ui {
class uidayreport;
}

class uidayreport : public QDialog
{
    Q_OBJECT

public:
    explicit uidayreport(QWidget *parent = nullptr);
    ~uidayreport();

private:
    Ui::uidayreport *ui;
};

#endif // UIDAYREPORT_H
