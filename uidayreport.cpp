#include "uidayreport.h"
#include "ui_uidayreport.h"
#include "dayreport.h"
#include <QDialogButtonBox>
#include <QDebug>

static DayReport* thisDayReport;
static QTextDocument *thisTextDocument;
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
    thisTextDocument = new QTextDocument();
    ui->ProcessText->setDocument(thisTextDocument);
    this->WriteOk = false;
    ui->setupUi(this);
    ResetConnect();
}

uidayreport::uidayreport(DayReport * dayreport):
    ui(new Ui::uidayreport)
{
    ui->setupUi(this);
    thisDayReport = dayreport;
    thisTextDocument = new QTextDocument();
    ui->ProcessText->setDocument(thisTextDocument);
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

QString uidayreport::SelfRead(QString InputString)
{

}

QDateTime * uidayreport::SelfRead(QDateTime Time)
{

}

void uidayreport::FinishReport()
{
    qDebug()<<ui->CaseText->currentText();
    //开始
    thisDayReport->SetCase(this->SelfRead(ui->CaseText->currentText()));
    thisDayReport->SetProduct(this->SelfRead(ui->ProductText->currentText()));
    thisDayReport->SetTarget(this->SelfRead(ui->TargetText->text()));
    thisDayReport->SetStartTime(this->SelfRead(ui->StartTimeText->dateTime()));
    //中间
    thisDayReport->SetProcess(this->SelfRead(ui->ProcessText->toPlainText()));
    //结束
    thisDayReport->SetEndTime(this->SelfRead(ui->CaseText->currentText()));
    thisDayReport->SetPriority(this->SelfRead(ui->ProductText->currentText()));
    thisDayReport->SetEvaluate(this->SelfRead(ui->TargetText->text()));
    thisDayReport->SetDiff(this->SelfRead(ui->StartTimeText->dateTime()));

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

