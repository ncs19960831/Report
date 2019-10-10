#include "uidayreport.h"
#include "ui_uidayreport.h"
#include "dayreport.h"
#include <QDialogButtonBox>
#include <QDebug>

static DayReport* thisDayReport;

void uidayreport::ResetConnect()
{
    QObject::connect(ui->WriteButton,SIGNAL(accepted()),this,SLOT(Accept()));
    QObject::connect(ui->WriteButton_2,SIGNAL(accepted()),this,SLOT(Accept()));
    QObject::connect(ui->WriteButton_3,SIGNAL(accepted()),this,SLOT(Accept()));
}


uidayreport::uidayreport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uidayreport)
{
    thisDayReport = new DayReport();
    this->WriteOk = false;
    ui->setupUi(this);
    ResetConnect();
}

uidayreport::uidayreport(DayReport * dayreport):
    ui(new Ui::uidayreport)
{
    ui->setupUi(this);
    thisDayReport = dayreport;
    this->WriteOk = false;
    ResetConnect();
}

uidayreport::~uidayreport()
{
    delete ui;
}

bool uidayreport::GetStatus()
{
    return this->WriteOk;
}

DayReport * uidayreport::GetReport()
{
    return thisDayReport;
}

void uidayreport::FinishReport()
{
    qDebug()<<ui->CaseText->currentText();
    thisDayReport->SetCase(ui->CaseText->currentText());
}

void uidayreport::Accept()
{
    this->WriteOk = true;
    FinishReport();
    this->close();
}

void uidayreport::Reject()
{
    this->WriteOk = false;
    this->close();
}

