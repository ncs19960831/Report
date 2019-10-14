#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dayreport.h"
#include "uidayreport.h"
#include "mainwindow.h"
#include <math.h>
#include <QObject>
#include <QTableWidget>
#include <ui_mainwindow.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->InitMainTable();
    this->InitFilterTable();
}




int MainWindow::InitMainTable()
{
    QTableWidget* TableWidget = ui->MainTableWidget;
    TableWidget->setColumnCount(10);
    TableWidget->setRowCount(10);
    TableWidget->setHorizontalHeaderLabels(QStringList()<< "序号"<<"机型"<<"事项"<<"目标"<<"实际进行"<<"差异及改善"<<"开始时间"<<"结束时间"<<"权重"<<"评估");

    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

    TableWidget->setItem(1,1,new QTableWidgetItem("Jan"));

    return 0;
}

int MainWindow::UpdateFilterTable()
{
    static QList<QString> list;
    QTableWidget* TableWidget = ui->FilterTableWidget;
    QComboBox * Combox;
    list.clear();
    list<<"序号"<<"机型"<<"事项"<<"目标"<<"实际进行"<<"差异及改善"<<"开始时间"<<"结束时间"<<"权重"<<"评估";

    for (int i = 0;i < TableWidget->rowCount();i++)
    {
        if ((TableWidget->item(i,1) != nullptr))
        {
            if (TableWidget->item(i,1)->text() == "")
                continue;
            Combox = (QComboBox*)TableWidget->cellWidget(i,0);
            list.removeOne(Combox->currentText());
        }

    }
    QStringList *StringList = new QStringList(list);
    for(int i = 0;i < TableWidget->rowCount();i++)
    {
        if (TableWidget->item(i,1) == nullptr)  //仅更新没有数据的窗口
        {
            if (TableWidget->currentRow() == i) //避免当前修改的单元格会被修改
                continue;
            FilterCombox[i]->clear();
            FilterCombox[i]->addItems(*StringList);
            TableWidget->setCellWidget(i,0,FilterCombox[i]);
        }
    }
    delete StringList;
}

int MainWindow::InitFilterTable()
{
    QStringList StringList;
    StringList<<"筛选项目"<<"起始"<<"结束";
    QTableWidget* TableWidget = ui->FilterTableWidget;
    TableWidget->setColumnCount(StringList.count());
    TableWidget->setRowCount(10);
    TableWidget->setHorizontalHeaderLabels(StringList);

    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
//    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

    for(int i = 0;i < TableWidget->rowCount();i++)
    {

        FilterCombox[i] = new QComboBox();
        FilterCombox[i]->addItems(QStringList()<<"序号"<<"机型"<<"事项"<<"目标"<<"实际进行"<<"差异及改善"<<"开始时间"<<"结束时间"<<"权重"<<"评估");
        TableWidget->setCellWidget(i,0,FilterCombox[i]);
    }

    return 0;
}

int MainWindow::SetDayreportToItem(DayReport* Dayreport,int Row)
{
    QString * string = new QString();
    QTableWidget* TableWidget = ui->MainTableWidget;
    QTableWidgetItem * TableWidgetItem = new QTableWidgetItem();
    Dayreport->GetCase(string);
    TableWidgetItem->setText(*string);
    Dayreport->GetDiff(string);
    TableWidgetItem->setText(*string);

    Dayreport->GetNumber(string);
    TableWidgetItem->setText(*string);
    Dayreport->GetTarget(string);
    TableWidgetItem->setText(*string);

    //Dayreport->GetEndTime(string);
    TableWidgetItem->setText(*string);
    Dayreport->GetProcess(string);
    TableWidgetItem->setText(*string);

    Dayreport->GetProduct(string);
    TableWidgetItem->setText(*string);
    Dayreport->GetEvaluate(string);
    TableWidgetItem->setText(*string);

    Dayreport->GetPriority(string);
    TableWidgetItem->setText(*string);
    //Dayreport->GetStartTime(string);
    TableWidgetItem->setText(*string);
    TableWidget->setCurrentItem(TableWidgetItem);

}



int MainWindow::GetItemToDayreport(DayReport* Dayreport,QString* DataString, int ItemIndex)
{
    QTableWidgetItem* TableWidgetItem = new QTableWidgetItem();
    QTableWidget* MainTableWidget = ui->MainTableWidget;
    if (MainTableWidget->currentRow() != 0)
    {
        return -1;
    }
    TableWidgetItem = MainTableWidget->currentItem();
    *DataString = TableWidgetItem->text();
    printf_s("%s",DataString);
    return 0;
}
int MainWindow::AddDayReport(int index)
{
    uidayreport * uidayreport = new class uidayreport((unsigned int)index);
    uidayreport->SetSelectIndex((unsigned int)index);
    uidayreport->exec();        //栓塞等待选择完成
    if (uidayreport->GetStatus())
    {
        DayReport * Dayreport = uidayreport->GetReport();
        SetDayreportToItem(Dayreport,1);
    }

    delete uidayreport;
    return 0;
}

int MainWindow::DelDayReport(int index)
{
    return 0;
}

int MainWindow::EditDayReport(int index)
{
    DayReport* Dayreport =new DayReport();
    QString* DataString= new QString();
    uidayreport * uidayreport = new class uidayreport((unsigned int)index);
    uidayreport->show();
    QTableWidget* MainTableWidget = ui->MainTableWidget;
    int Row = MainTableWidget->currentRow();
    this->GetItemToDayreport(Dayreport,DataString,Row);
    return 0;
}

void MainWindow::on_pushButton_2_clicked()
{

    int index = ui->comboBox->currentIndex();

    switch (index) {
    case 0: {       //add
        AddDayReport(index);
    }break;
    case 2:{        //del
        DelDayReport(index);
    }break;
    case 1:{        //modify
        EditDayReport(index);
    }break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FilterTableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    MainWindow::UpdateFilterTable();

}
