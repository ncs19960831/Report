#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dayreport.h"
#include "uidayreport.h"
#include "mainwindow.h"
#include <math.h>
#include <QObject>
#include <QDebug>
#include <QTableWidget>
#include <QTableView>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include "datamanage.h"
 DataManage* thisDataManage ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->InitMainTable();
    this->InitFilterTable();

}


void MainWindow::AboutMsg()
{
    QMessageBox::about(this,tr("版本信息"),tr("现在版本为0.0.01"));
}

int MainWindow::InitMainTable()
{
    QTableView * TableView = ui->MainTableView;
    thisDataManage = new DataManage (TableView) ;
    TableView->hideColumn(0);
    TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑

    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    return 0;
}

int MainWindow::UpdateFilterTable()
{
    static QList<QString> list;
    QTableWidget* TableWidget = ui->FilterTableWidget;
    QComboBox * Combox = new QComboBox () ;
    list.clear();
    list<<"序号"<<"机型"<<"事项"<<"目标"<<"实际进行"<<"差异及改善"<<"开始时间"<<"结束时间"<<"权重"<<"评估";
    //遍历当前所有的按钮，发现已经设置的项目之后，将其删除掉。
    for (int i = 0;i < TableWidget->rowCount();i++)
    {
        if ((TableWidget->item(i,1) != nullptr))
        {
            if (TableWidget->item(i,1)->text() == "")
                continue;
            //提取当前的下拉菜单，然后删除当前的选项
            Combox = (QComboBox*)TableWidget->cellWidget(i,0);
            list.removeOne(Combox->currentText());
        }

    }
    //将整理完成的数据重新放置进入筛选窗口的空白筛选项
    QStringList *StringList = new QStringList(list);
    QDateTimeEdit* DateTimeEdit = new QDateTimeEdit();

    for(int i = 0;i < TableWidget->rowCount();i++)
    {
        if (TableWidget->item(i,1) == nullptr)  //仅更新没有数据的窗口
        {
            if (TableWidget->currentRow() == i) //避免当前修改的单元格会被修改
            {
                /*Combox = (QComboBox*)TableWidget->cellWidget(i,0);
                QString ssss = Combox->currentText();
                qDebug()<<ssss <<endl;
                qDebug()<<Combox->currentText().indexOf("时间")<<endl;
                if (Combox->currentText().indexOf("时间")>0)
                {
                    TableWidget->setCellWidget(i,1,DateTimeEdit);
                }*/
                continue;
            }
            Combox = (QComboBox*)TableWidget->cellWidget(i,0);
            QObject::disconnect(Combox,SIGNAL(currentTextChange),this,SLOT(SwitchDateTime));
            FilterCombox[i]->clear();
            FilterCombox[i]->addItems(*StringList);
            QObject::connect(FilterCombox[i],SIGNAL(currentTextChange),this,SLOT(SwitchDateTime));
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
    thisDataManage->SetNewData(Row,Dayreport);

}

int MainWindow::EditDayreportToItem(DayReport* Dayreport,int Row)
{
    thisDataManage->EditData(Row,Dayreport);

}

int MainWindow::GetItemToDayreport(DayReport* Dayreport, int ItemIndex)
{
    QTableView* MainTableView = ui->MainTableView;
    DataManage* DataManage = thisDataManage;
    if (MainTableView->model()->rowCount() <= 0)
    {
        return -1;
    }
    DataManage->GetOneData(ItemIndex,Dayreport);

    return 0;
}
int MainWindow::AddDayReport(int index)
{
    uidayreport * uidayreport = new class uidayreport(index);
    DayReport* Dayreport = new DayReport();

    //    uidayreport->SetSelectIndex(index);
    uidayreport->exec();        //栓塞等待选择完成
    if (uidayreport->GetStatus())
    {
            Dayreport = uidayreport->GetReport();
            SetDayreportToItem(Dayreport,index);

    }

    delete uidayreport;
    return 0;
}

int MainWindow::DelDayReport(int index)
{
    thisDataManage->DelData(index);
    return 0;
}

int MainWindow::EditDayReport(int index)
{
    DayReport* Dayreport =new DayReport();
    GetItemToDayreport(Dayreport,index);
    uidayreport * uidayreport = new class uidayreport(Dayreport,(unsigned int)index);
    uidayreport->exec();
    if (uidayreport->GetStatus())
    {
        DayReport * Dayreport = uidayreport->GetReport();
        EditDayreportToItem(Dayreport,index);
    }
    return 0;
}

void MainWindow::on_pushButton_2_clicked()
{

    int index = ui->MainTableView->currentIndex().row();
    if (index<0)
    {
        index = ui->MainTableView->model()->rowCount();
    }
    int Select = ui->comboBox->currentIndex();
    index++;
    switch (Select) {
    case 0: {       //add
        AddDayReport(index);
    }break;
    case 2:{        //del
        index--;
        DelDayReport(index);
    }break;
    case 1:{        //modify
        EditDayReport(index);
    }break;
    default:
        break;
    }
    thisDataManage->SortNumber();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FilterTableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    MainWindow::UpdateFilterTable();

}


QVariantMap MainWindow::GetFilterList()
{
    QTableWidget* TableWidget = ui->FilterTableWidget;
    QVariantMap ret;
    QString String = TableWidget->item(1,1)->text();
    for (int i = 0;i<TableWidget->rowCount();i++)
    {
        String = TableWidget->item(i,1)->text();
        QVariant Value = TableWidget->item(i,2)->text();
    }
//    ret.insert()
}

void MainWindow::on_About_triggered()
{
    this->AboutMsg();
}

void MainWindow::on_Report_clicked()
{
    DataManage* Datamanage = thisDataManage;
    Datamanage->SaveDataBase();
}
