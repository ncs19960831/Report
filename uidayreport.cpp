#include "uidayreport.h"
#include "ui_uidayreport.h"

uidayreport::uidayreport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uidayreport)
{
    ui->setupUi(this);
}

uidayreport::~uidayreport()
{
    delete ui;
}
