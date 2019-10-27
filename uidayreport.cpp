#include "uidayreport.h"
#include "ui_uidayreport.h"
#include "dayreport.h"
#include <QDialogButtonBox>
#include <QDebug>

static DayReport* thisDayReport;
static int thisSelectIndex;
void uidayreport::ResetConnect()
{
    this->WriteOk = false;
    QObject::connect(ui->WriteButton,SIGNAL(accepted()),this,SLOT(Accept()));
    QObject::connect(ui->WriteButton_2,SIGNAL(accepted()),this,SLOT(Accept()));
    QObject::connect(ui->WriteButton_3,SIGNAL(accepted()),this,SLOT(Accept()));
}

void uidayreport::SetSelectIndex(int Index)
{
    thisSelectIndex = Index;
    thisDayReport = new DayReport(QString(thisSelectIndex)) ;
}

uidayreport::uidayreport(int Index,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uidayreport)
{
    thisSelectIndex = Index;
    QString String = QString(thisSelectIndex+0x30);
    thisDayReport = new DayReport(String);
    this->WriteOk = false;
    ui->setupUi(this);
    ui->NameText->setText(String);

    ResetConnect();
}

uidayreport::uidayreport(DayReport * dayreport,int Index):
    ui(new Ui::uidayreport)
{
    ui->setupUi(this);
    thisDayReport = dayreport;
    thisSelectIndex = Index;
    QString String = QString(thisSelectIndex+0x30);
    if (thisDayReport->GetNumber(new QString()) == false)
    {
        thisDayReport = new DayReport(String);
    }
    ui->NameText->setText(String);
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

QString uidayreport::SelfRead(QComboBox* InputString)
{
    QString String = "";
    if (InputString->currentText() == nullptr)
        return String;
    if (InputString->currentText() == "")
        return String;
    String = InputString->currentText();
    return String;

}

QString uidayreport::SelfRead(QLineEdit* InputString)
{
    QString String = "";
    if (InputString->text() == nullptr)
        return String;
    if (InputString->text() == "")
        return String;
    String = InputString->text();
    return String;
}

QString uidayreport::SelfRead(QTextEdit* InputString)
{
    QString String = "";
    if (InputString->toPlainText() == nullptr)
        return String;
    if (InputString->toPlainText() == "")
        return String;
    String = InputString->toPlainText();//暂时不选择显示图片
    return String;
}

QDateTime * uidayreport::SelfRead(QDateTimeEdit* DateTime)
{
    QDate* DateNormal = new QDate(2000,1,1);
    QTime* TimeNormal = new QTime(1,1,1,0);
    QDateTime* String =new QDateTime(DateNormal->currentDate(),TimeNormal->currentTime());

    if (DateTime->dateTime().toString() == "")
        return String;
    if (DateTime->dateTime().isNull())
        return String;
    *String = DateTime->dateTime();
    return String;
}

void uidayreport::FinishReport()
{
    //序号
    thisDayReport->SetNumber(QString(thisSelectIndex+0x30));
    //开始
    thisDayReport->SetCase(this->SelfRead(ui->CaseText));
    thisDayReport->SetProduct(this->SelfRead(ui->ProductText));
    thisDayReport->SetTarget(this->SelfRead(ui->TargetText));
    thisDayReport->SetStartTime(this->SelfRead(ui->StartTimeText));
    //中间
    thisDayReport->SetProcess(this->SelfRead(ui->ProcessText));
    //结束
    thisDayReport->SetEndTime(this->SelfRead(ui->EndTimeText));
    thisDayReport->SetPriority(this->SelfRead(ui->ProductText));
    thisDayReport->SetEvaluate(this->SelfRead(ui->TargetText));
    thisDayReport->SetDiff(this->SelfRead(ui->DiffText));

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

